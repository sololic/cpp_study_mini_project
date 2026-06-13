// Copyright 2025 Tesollo
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the Tesollo nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#include <chrono>   // 뭐지 -> 시간 표준 라이브러리? std::chrono::xxx 처럼 명시적으로 호출하진 않음
#include <vector>   // 아마 리스트등 쓰려고?
#include <memory>   // 저장하기 위한 용도가 뭐 있는듯? -> 스마트 포인터 제공 헤더 : std::make_shared<JointTrajectoryPublisher>()
#include <string>   // 문자열
#include "rclcpp/rclcpp.hpp"    // ROS2 C++ 라이브러리 일듯? 파이썬의 import rclpy와 같은 역할

// 그리퍼 패키지 메시지 타입 종류? -> 아님
// ROS2 표준 공통 패키지인 trajectory_msgs의 메시지 타입
// JointTrajectory: 여러 joint의 이름 + trajectory point들의 리스트
// JointTrajectoryPoint: 특정 시점의 각 joint 위치/속도/가속도 + 도달 시간
// -> 이 타입들을 이용해서 로봇의 joint 움직임 명령을 표현할듯?
#include "trajectory_msgs/msg/joint_trajectory.hpp"        
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"   

// chrono_literals라는 이름을 앞에 붙이는 역할? 파이썬과 같은 역할인가
// std::chrono_literals::operator""s    
using namespace std::chrono_literals;   

// constexpr? 이거 뭐야 
// double형식의 문자열 쓰고 d2r이라는 함수 선언하고 deg값을 인자로 받아서 라디안 변환해주는거?
constexpr double d2r(double deg) {
    return deg * 3.141592 / 180.0;
}

// JointTrajectoryPublisher 클래스 선언하는거 같고 public으로 다른곳에서 이용할수 있게 하고 rclcpp::Node 이게 아마 cpp의 노드 선언? init_node 같은 느낌인듯
class JointTrajectoryPublisher : public rclcpp::Node {
public:
    // 어.. joint_trajectory_publisher라는 이름의 노드 생성하고 index_ 0으로 초기화하는거지 않을까
    JointTrajectoryPublisher() : Node("joint_trajectory_publisher"), index_(0) {
        // this는 잘 모르겠는데 trajectory_msgs 메시지 타입의 JointTrajectory타입을 이용해 /dg3f_m_controller/joint_trajectory라는 토픽 publisher 생성? queue_size는 10?
        // this는 현재 객체(자기 자신)를 가리키는 포인터입니다. 그래서 this->create_publisher<...>(...)는 "이 객체의 멤버 함수 create_publisher를 호출해서 퍼블리셔를 생성한다"는 의미입니다.
        publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
            "/dg3f_m_controller/joint_trajectory", 10);
        // create_wall_timer로 2초마다 JointTrajectoryPublisher 클래스의 timer_callback 함수 실행? bind는 몰루
        // create_wall_timer는 인자 없는 콜백(callable)을 기대하는데, timer_callback은 멤버 함수라서 호출할 때 어떤 객체(this)의 함수인지 알아야 해요. std::bind(&Class::timer_callback, this)는 "이 멤버 함수 + 이 객체"를 묶어서 인자 없이 호출 가능한 콜백 하나로 만들어주는 역할입니다.
        timer_ = this->create_wall_timer(2s,
             std::bind(&JointTrajectoryPublisher::timer_callback, this));
        
        // joint_names_에 각 joint 매핑할듯?
        joint_names_ = {
            "j_dg_1_1", "j_dg_1_2", "j_dg_1_3", "j_dg_1_4",
            "j_dg_2_1", "j_dg_2_2", "j_dg_2_3", "j_dg_2_4",
            "j_dg_3_1", "j_dg_3_2", "j_dg_3_3", "j_dg_3_4"
        };

        // angles_에 각 joint의 각도 값 저장 처음은 다 0 -> 3,4 joint 기준 1 -> 2 -> 3핑거만 80도 구부리기
        angles_ = {
            {0,        0,       d2r(0), d2r(0), // 1번 핑거 joint 1,2,3,4
             0,        0,        0,        0,   // 2번 핑거 joint 1,2,3,4
             0,        0,        0,        0},  // 3번 핑거 joint 1,2,3,4

             {0,        0,       d2r(80), d2r(80),
             0,        0,        0,        0,
             0,        0,        0,        0},

            {0,        0,        0,        0,
             0,        0,        d2r(80), d2r(80),
             0,        0,        0,        0},

            {0,        0,        0,        0,
             0,        0,        0,        0,
             0,        0,        d2r(80),  d2r(80)},
        };
    }

// 다른 곳에서 이용 못하게
private:
    // timer_callback 선언
    void timer_callback() {
        // JointTrajectory 타입의 msg 객체 생성 joint_names_ 저장
        trajectory_msgs::msg::JointTrajectory msg;
        msg.joint_names = joint_names_;

        trajectory_msgs::msg::JointTrajectoryPoint point;
        point.positions = angles_[index_];
        point.time_from_start = rclcpp::Duration(1s);

        msg.points.push_back(point);
        RCLCPP_INFO(this->get_logger(), "Publishing trajectory #%zu", index_);
        publisher_->publish(msg);

        index_++;
        if (index_ >= angles_.size()) {
            index_ = 0;
        }
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr publisher_;
    std::vector<std::string> joint_names_;
    std::vector<std::vector<double>> angles_;
    size_t index_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JointTrajectoryPublisher>());
    rclcpp::shutdown();
    return 0;
}
