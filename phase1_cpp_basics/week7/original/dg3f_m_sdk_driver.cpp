#include <cstring>
#include <mutex>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#include "DGSDK.h"
#include "DGDataTypes.h"

using namespace std::chrono_literals;

std::vector<std::string> joint_names = {
    "j_dg_1_1", "j_dg_1_2", "j_dg_1_3", "j_dg_1_4",
    "j_dg_2_1", "j_dg_2_2", "j_dg_2_3", "j_dg_2_4",
    "j_dg_3_1", "j_dg_3_2", "j_dg_3_3", "j_dg_3_4"};

// DGSDK 콜백은 SDK 내부 스레드에서 호출되므로 mutex로 보호
std::mutex g_data_mutex;
ReceivedGripperData g_latest_data = {};

void on_received_data(const ReceivedGripperData data) {
  std::lock_guard<std::mutex> lock(g_data_mutex);
  g_latest_data = data;
}

void on_connected() {}
void on_disconnected() {}

class DG3FSDKDriver : public rclcpp::Node {
 public:
  DG3FSDKDriver() : Node("DG3FSDKDriver") {
    this->declare_parameter<std::string>("ip", "169.254.186.72");
    this->declare_parameter<int>("port", 502);

    std::string ip;
    int port;
    this->get_parameter("ip", ip);
    this->get_parameter("port", port);

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

    for (int i = 0; i < 10; i++) {
      rclcpp::sleep_for(std::chrono::milliseconds(500));
      DG_RESULT r = SystemStart();
      RCLCPP_INFO(this->get_logger(), "SystemStart attempt %d: %d", i, r);
      if (r == 0) break;
    }

    timer_ = this->create_wall_timer(
        50ms, std::bind(&DG3FSDKDriver::timer_callback, this));
  }

  ~DG3FSDKDriver() {
    if (timer_) {
      timer_->cancel();
    }
    DisconnectToGripper();
  }

 private:
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

  void grasp_callback(const std_msgs::msg::Bool::SharedPtr msg) {
    int is_grasp = msg->data ? 1 : 0;
    DG_RESULT r = StartGraspMotion(is_grasp);
    RCLCPP_INFO(this->get_logger(), "StartGraspMotion(%d): %d", is_grasp, r);
  }

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

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr moving_publisher_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr target_arrived_publisher_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr grasp_subscription_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DG3FSDKDriver>());
  rclcpp::shutdown();
}