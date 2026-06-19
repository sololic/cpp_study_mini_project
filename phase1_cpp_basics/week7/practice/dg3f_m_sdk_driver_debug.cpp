/*
 * =============================================================================
 * dg3f_m_sdk_driver_debug.cpp
 * 원본: week7/original/dg3f_m_sdk_driver.cpp (수정 금지, 그대로 둠)
 * 이 파일은 구조 파악용 주석만 추가한 디버그/참고 버전입니다.
 * =============================================================================
 *
 * [전체 블록 계층 구조 목차]
 *
 * 1. 전역 설정 (Global Setup)
 *   1.1 조인트 이름 정의
 *   1.2 SDK 콜백 공유 데이터 (mutex + g_latest_data)
 *   1.3 SDK 콜백 함수들
 *     1.3.1 on_received_data   - 그리퍼 데이터 수신 콜백
 *     1.3.2 on_connected       - 연결 성공 콜백
 *     1.3.3 on_disconnected    - 연결 종료 콜백
 *
 * 2. DG3FSDKDriver 클래스 (rclcpp::Node)
 *   2.1 생성자
 *     2.1.1 파라미터 선언 및 읽기 (ip, port)
 *     2.1.2 퍼블리셔/서브스크라이버 생성
 *     2.1.3 SDK 시스템 설정 및 연결 (SetGripperSystem, ConnectToGripper)
 *     2.1.4 SDK 옵션 설정 (SetGripperOption)
 *     2.1.5 SystemStart 재시도 루프
 *     2.1.6 주기 타이머 생성 (50ms)
 *   2.2 소멸자 (DisconnectToGripper)
 *   2.3 topic_callback   - /target_joint 구독 콜백
 *   2.4 grasp_callback   - /gripper/grasp_cmd 구독 콜백
 *   2.5 timer_callback   - 50ms 주기 상태 publish
 *   2.6 멤버 변수 선언부
 *
 * 3. main()
 *
 * -----------------------------------------------------------------------------
 * [블록 간 호출 관계]
 *
 * - [블록 3] main()
 *     └─ rclcpp::spin() 안에서 [블록 2.1] 생성자 1회 실행
 *
 * - [블록 2.1.2] 퍼블리셔/서브스크라이버 생성
 *     └─ /target_joint 토픽 수신 시 [블록 2.3] topic_callback 호출
 *     └─ /gripper/grasp_cmd 토픽 수신 시 [블록 2.4] grasp_callback 호출
 *
 * - [블록 2.1.3] SDK 시스템 설정 및 연결
 *     └─ SDK 콜백 등록: 데이터 수신 시 [블록 1.3.1] on_received_data,
 *        연결 시 [블록 1.3.2] on_connected, 연결 끊김 시 [블록 1.3.3] on_disconnected
 *        → SDK 내부 스레드에서 호출됨 (ROS 노드 스레드와 다름)
 *
 * - [블록 2.1.6] 주기 타이머 생성
 *     └─ 50ms마다 [블록 2.5] timer_callback 호출
 *
 * - [블록 2.5] timer_callback
 *     └─ [블록 1.2] g_latest_data 를 mutex로 보호하며 읽음
 *        (이 데이터는 [블록 1.3.1] on_received_data 가 SDK 스레드에서 갱신)
 *
 * - [블록 2.2] 소멸자
 *     └─ DisconnectToGripper() 호출 (SDK 연결 종료)
 *
 * =============================================================================
 */

#include <cstring>
#include <mutex>  // mutex.lock() -> python : threading.Lock()
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#include "DGSDK.h"
#include "DGDataTypes.h"

using namespace std::chrono_literals;

/* ════════════════════════════════════════════════════════════════════════════
 * [블록 1.1] 조인트 이름 정의
 *   - DG3F-M (3손가락 x 4관절 = 12관절)의 joint_states 메시지에 들어갈 이름들
 * ════════════════════════════════════════════════════════════════════════════ */
std::vector<std::string> joint_names = {
    "j_dg_1_1", "j_dg_1_2", "j_dg_1_3", "j_dg_1_4",
    "j_dg_2_1", "j_dg_2_2", "j_dg_2_3", "j_dg_2_4",
    "j_dg_3_1", "j_dg_3_2", "j_dg_3_3", "j_dg_3_4"};

/* ════════════════════════════════════════════════════════════════════════════
 * [블록 1.2] SDK 콜백 공유 데이터
 *   - DGSDK 콜백은 SDK 내부 스레드에서 호출되므로, ROS 노드 스레드와
 *     동시에 접근될 수 있음 → mutex로 보호해야 함
 * ════════════════════════════════════════════════════════════════════════════ */
std::mutex g_data_mutex;
ReceivedGripperData g_latest_data = {};

/* ════════════════════════════════════════════════════════════════════════════
 * [블록 1.3.1] on_received_data - 그리퍼 데이터 수신 콜백
 *   호출 주체: DGSDK 내부 스레드 (CallbackForOnReceivedGripperData로 등록됨, [블록 2.1.3] 참고)
 *   동작: 최신 데이터를 g_latest_data([블록 1.2])에 mutex로 보호하며 복사
 *   참고: [블록 2.5] timer_callback이 이 데이터를 읽어서 publish
 * ════════════════════════════════════════════════════════════════════════════ */
void on_received_data(const ReceivedGripperData data) {
  std::lock_guard<std::mutex> lock(g_data_mutex);
  g_latest_data = data;
}

/* ════════════════════════════════════════════════════════════════════════════
 * [블록 1.3.2] on_connected - 연결 성공 콜백 (현재 내용 없음)
 * [블록 1.3.3] on_disconnected - 연결 종료 콜백 (현재 내용 없음)
 *   등록 위치: [블록 2.1.3]
 * ════════════════════════════════════════════════════════════════════════════ */
void on_connected() {}
void on_disconnected() {}

/* ════════════════════════════════════════════════════════════════════════════
 * [블록 2] DG3FSDKDriver 클래스 (rclcpp::Node 상속)
 * ════════════════════════════════════════════════════════════════════════════ */
class DG3FSDKDriver : public rclcpp::Node {
 public:
  /* ──────────────────────────────────────────────────────────────────────
   * [블록 2.1] 생성자
   * ────────────────────────────────────────────────────────────────────── */
  DG3FSDKDriver() : Node("DG3FSDKDriver") {
    /* ----------------------------------------------------------------
     * [블록 2.1.1] 파라미터 선언 및 읽기
     *   - ip, port를 런치 파라미터로 받음 (기본값: 169.254.186.72:502)
     * ---------------------------------------------------------------- */
    this->declare_parameter<std::string>("ip", "169.254.186.72");
    this->declare_parameter<int>("port", 502);

    std::string ip;
    int port;
    this->get_parameter("ip", ip);
    this->get_parameter("port", port);

    /* ----------------------------------------------------------------
     * [블록 2.1.2] 퍼블리셔/서브스크라이버 생성
     *   - 발행: /joint_states, /gripper/moving, /gripper/target_arrived
     *   - 구독: /target_joint        → [블록 2.3] topic_callback
     *   - 구독: /gripper/grasp_cmd   → [블록 2.4] grasp_callback
     * ---------------------------------------------------------------- */
    publisher_ = this->create_publisher<sensor_msgs::msg::JointState>(
        "/joint_states", 10);

    moving_publisher_ = this->create_publisher<std_msgs::msg::Bool>(
        "/gripper/moving", 10);
    target_arrived_publisher_ = this->create_publisher<std_msgs::msg::Bool>(
        "/gripper/target_arrived", 10);

    subscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "/target_joint", 10,
        std::bind(&DG3FSDKDriver::topic_callback, this, std::placeholders::_1));

    grasp_subscription_ = this->create_subscription<std_msgs::msg::Bool>(
        "/gripper/grasp_cmd", 10,
        std::bind(&DG3FSDKDriver::grasp_callback, this, std::placeholders::_1));

    /* ----------------------------------------------------------------
     * [블록 2.1.3] SDK 시스템 설정 및 연결
     *   - GripperSystemSetting 구조체 채우고 SetGripperSystem 호출
     *   - SDK 콜백 등록: on_received_data([블록 1.3.1]), on_connected([블록 1.3.2]),
     *                    on_disconnected([블록 1.3.3])
     *   - ConnectToGripper() 호출 후 2초 대기 (연결 안정화)
     * ---------------------------------------------------------------- */
    GripperSystemSetting sys = {};
    strncpy(sys.ip, ip.c_str(), sizeof(sys.ip) - 1);
    sys.port = port;
    sys.readTimeout = 1000;
    sys.controlMode = CONTROL_MODE_OPERATOR;
    sys.communicationMode = COMMUNICATION_MODE_ETHERNET;
    sys.slaveID = 1;

    SetGripperSystem(sys);
    CallbackForOnConnected(on_connected);
    CallbackForOnDisconnected(on_disconnected);
    CallbackForOnReceivedGripperData(on_received_data);

    RCLCPP_INFO(this->get_logger(), "ConnectToGripper: %d", ConnectToGripper());

    RCLCPP_INFO(this->get_logger(), "Waiting 2s for connection to stabilize...");
    rclcpp::sleep_for(std::chrono::seconds(2));

    /* ----------------------------------------------------------------
     * [블록 2.1.4] SDK 옵션 설정
     *   - GripperSetting 구조체에 모델, 관절/손가락 수, 수신 데이터 타입 설정
     *   - SetGripperOption 호출
     * ---------------------------------------------------------------- */
    GripperSetting opt = {};
    opt.movingInpose = 0.5f;
    opt.jointCount = 12;
    opt.fingerCount = 3;
    opt.model = DG_MODEL_DG_3F_B;
    opt.dutyByteLength = 5;
    opt.receivedDataType[0] = DEVELOPER_MODE_RECEIVED_DATA_TYPE_JOINT;
    opt.receivedDataType[1] = DEVELOPER_MODE_RECEIVED_DATA_TYPE_CURRENT;
    opt.receivedDataType[2] = DEVELOPER_MODE_RECEIVED_DATA_TYPE_TEMPERATURE;
    opt.receivedDataType[3] = DEVELOPER_MODE_RECEIVED_DATA_TYPE_VELOCITY;

    RCLCPP_INFO(this->get_logger(), "SetGripperOption: %d", SetGripperOption(opt));

    /* ----------------------------------------------------------------
     * [블록 2.1.5] SystemStart 재시도 루프
     *   - 500ms 간격으로 최대 10회 SystemStart() 시도
     *   - 성공(0) 시 즉시 루프 종료
     * ---------------------------------------------------------------- */
    for (int i = 0; i < 10; i++) {
      rclcpp::sleep_for(std::chrono::milliseconds(500));
      DG_RESULT r = SystemStart();
      RCLCPP_INFO(this->get_logger(), "SystemStart attempt %d: %d", i, r);
      if (r == 0) break;
    }

    /* ----------------------------------------------------------------
     * [블록 2.1.6] 주기 타이머 생성
     *   - 50ms마다 [블록 2.5] timer_callback 호출
     * ---------------------------------------------------------------- */
    timer_ = this->create_wall_timer(
        50ms, std::bind(&DG3FSDKDriver::timer_callback, this));
  }

  /* ──────────────────────────────────────────────────────────────────────
   * [블록 2.2] 소멸자
   *   - 타이머 정지 + DisconnectToGripper()로 SDK 연결 종료
   * ────────────────────────────────────────────────────────────────────── */
  ~DG3FSDKDriver() {
    if (timer_) {
      timer_->cancel();
    }
    DisconnectToGripper();
  }

 private:
  /* ──────────────────────────────────────────────────────────────────────
   * [블록 2.3] topic_callback - /target_joint 구독 콜백
   *   입력: Float64MultiArray (12개 값, radian)
   *   동작: radian → degree 변환 후 MoveJointAll() 호출
   *   호출 주체: ROS 노드 스레드 (구독 등록은 [블록 2.1.2])
   * ────────────────────────────────────────────────────────────────────── */
  void topic_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->data.size() != 12) {
      RCLCPP_WARN(this->get_logger(), "/target_joint expects 12 values, got %zu",
                  msg->data.size());
      return;
    }

    float target[12];
    for (int i = 0; i < 12; i++) {
      target[i] = static_cast<float>(msg->data[i] * 180.0 / M_PI);
    }

    DG_RESULT r = MoveJointAll(target);
    RCLCPP_INFO(this->get_logger(), "MoveJointAll: %d", r);
  }

  /* ──────────────────────────────────────────────────────────────────────
   * [블록 2.4] grasp_callback - /gripper/grasp_cmd 구독 콜백
   *   입력: Bool (true=grasp, false=release)
   *   동작: StartGraspMotion() 호출
   *   호출 주체: ROS 노드 스레드 (구독 등록은 [블록 2.1.2])
   * ────────────────────────────────────────────────────────────────────── */
  void grasp_callback(const std_msgs::msg::Bool::SharedPtr msg) {
    int is_grasp = msg->data ? 1 : 0;
    DG_RESULT r = StartGraspMotion(is_grasp);
    RCLCPP_INFO(this->get_logger(), "StartGraspMotion(%d): %d", is_grasp, r);
  }

  /* ──────────────────────────────────────────────────────────────────────
   * [블록 2.5] timer_callback - 50ms 주기 상태 publish
   *   동작:
   *     1) [블록 1.2] g_latest_data를 mutex로 보호하며 복사
   *     2) /joint_states (position: rad, effort: A) 발행
   *     3) /gripper/moving, /gripper/target_arrived 발행
   *   호출 주체: ROS 노드 타이머 스레드 (등록은 [블록 2.1.6])
   * ────────────────────────────────────────────────────────────────────── */
  void timer_callback() {
    ReceivedGripperData data;
    {
      std::lock_guard<std::mutex> lock(g_data_mutex);
      data = g_latest_data;
    }

    auto joint_state = sensor_msgs::msg::JointState();
    joint_state.header.stamp = this->get_clock()->now();
    joint_state.name = joint_names;

    joint_state.position.resize(12);
    joint_state.effort.resize(12);
    for (int i = 0; i < 12; i++) {
      joint_state.position[i] = data.joint[i] * M_PI / 180.0;
      joint_state.effort[i] = data.current[i] / 1000.0;
    }

    publisher_->publish(joint_state);

    auto moving_msg = std_msgs::msg::Bool();
    moving_msg.data = (data.moving != 0);
    moving_publisher_->publish(moving_msg);

    auto target_arrived_msg = std_msgs::msg::Bool();
    target_arrived_msg.data = (data.targetArrived != 0);
    target_arrived_publisher_->publish(target_arrived_msg);
  }

  /* ──────────────────────────────────────────────────────────────────────
   * [블록 2.6] 멤버 변수 선언부
   * ────────────────────────────────────────────────────────────────────── */
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr moving_publisher_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr target_arrived_publisher_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr grasp_subscription_;
};

/* ════════════════════════════════════════════════════════════════════════════
 * [블록 3] main()
 *   - rclcpp 초기화 → DG3FSDKDriver 노드 생성 → spin → shutdown
 * ════════════════════════════════════════════════════════════════════════════ */
int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DG3FSDKDriver>());
  rclcpp::shutdown();
}
