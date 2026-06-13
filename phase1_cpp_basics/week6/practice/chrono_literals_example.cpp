#include <iostream>
#include <chrono> // chrono 라이브러리 안 chrono_literals 네임스페이스가 정의되어 있음
// duration : 시간의 길이/양 (예: 2초, 500밀리초) / C++ 클래스 타입
// time_point : 특정 시점 (예: 현재 시각, 5초 후 시각)

int main() {
    // 1. using namespace 없이 정식 표기
    //    std::chrono::seconds 타입의 객체를 생성
    std::chrono::seconds sec1 = std::chrono::seconds(2);
    std::cout << "sec1 (정식 표기) = " << sec1.count() << "s\n";

    // 2. using namespace std::chrono_literals; 를 쓰면
    //    아래처럼 "2s" 라는 리터럴만으로 같은 객체를 만들 수 있음
    using namespace std::chrono_literals;   // **"리터럴 접미사(s, ms, min 등) 문법 자체를 활성화"**

    std::chrono::seconds sec2 = 2s;
    std::cout << "sec2 (리터럴 표기) = " << sec2.count() << "s\n";
    // std::cout << "sec2 (리터럴 표기) = " << 2s << "s\n";

    using std::chrono_literals::operator""s;
    auto sec = 2s;
    std::cout << "sec (리터럴 표기) = " << sec.count() << "s\n";

    // 3. ms, min 같은 다른 시간 단위 리터럴도 동일하게 제공됨
    std::chrono::milliseconds ms = 500ms;
    std::chrono::minutes min = 1min;
    

    std::cout << "ms  = " << ms.count() << "ms\n";
    std::cout << "min = " << min.count() << "min\n";

    // 4. dg3f_m_test.cpp 에서 쓰인 것과 동일한 패턴
    //    create_wall_timer(2s, ...) / rclcpp::Duration(1s)
    //    -> 여기서 2s, 1s 가 바로 std::chrono::seconds(2), std::chrono::seconds(1)
    auto timer_period = 2s;
    auto duration = 1s;
    std::cout << "timer_period = " << timer_period.count() << "s\n";
    std::cout << "duration     = " << duration.count() << "s\n";

    // 5. test
    auto now = std::chrono::system_clock::now();  // 현재 시각 (time_point)
    auto later = now + 5s;                          // 5초 후 시각 (time_point)
    auto diff = later - now;                        // 다시 duration (5s)
    // auto later2 = now + 5; // error: invalid operands to binary expression ('std::chrono::time_point<std::chrono::system_clock>' and 'int')
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::time_t l = std::chrono::system_clock::to_time_t(later);
    
    std::cout << std::ctime(&t);  // "Sat Jun 13 ... 2026" 같은 형태로 출력
    std::cout << std::ctime(&l);

    std::cout << "현재 시각: " << std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() << "s\n";
    std::cout << "5초 후 시각: " << std::chrono::duration_cast<std::chrono::seconds>(later.time_since_epoch()).count() << "s\n";
    std::cout << "시간 차이: " << std::chrono::duration_cast<std::chrono::seconds>(diff).count() << "s\n";
    // std::cout << "5초 후 시각 (later2): " << std::chrono::duration_cast<std::chrono::seconds>(later2.time_since_epoch()).count() << "s\n";

    return 0;
}
