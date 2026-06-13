#include <iostream>

// 일반 함수 - 항상 실행 시점(runtime)에 계산됨
double d2r_normal(double deg) {
    return deg * 3.141592 / 180.0;
}

// constexpr 함수 - 인자가 상수면 컴파일 시점(compile-time)에 계산 가능
constexpr double d2r(double deg) {
    return deg * 3.141592 / 180.0;
}

int main() {
    // 1. 인자가 상수(리터럴) -> 컴파일 시점에 미리 계산됨
    constexpr double r1 = d2r(80);
    std::cout << "d2r(80) = " << r1 << "\n";

    // 2. constexpr 변수는 배열 크기 같은 "컴파일 시점에 정해져야 하는 곳"에도 사용 가능

    // int ar = 4;
    // int arr[ar];  // error: va  riable length array ‘arr’ is used [-Werror=vla]

    // const int m = 5;  // const도 런타임에 결정될 수 있기 때문에 컴파일 시점 상수가 아님
    // int arr[m];  // error: variable length array ‘arr2’ is

    constexpr int n = 5;
    int arr[n];  // 일반 변수였다면 컴파일 에러 (배열 크기는 컴파일 시점 상수여야 함)
    for (int i = 0; i < n; ++i) arr[i] = i * i;
    std::cout << "arr[4] = " << arr[4] << "\n";

    // 3. 인자가 변수(runtime 값)면, constexpr 함수도 그냥 일반 함수처럼 동작
    double user_input = 45.0;  // 실행 중에 정해지는 값이라고 가정
    double r2 = d2r(user_input);
    std::cout << "d2r(45) = " << r2 << "\n";

    // 4. d2r_normal과 d2r 둘 다 결과는 같음 - 차이는 "언제 계산되느냐"
    std::cout << "d2r_normal(80) = " << d2r_normal(80) << "\n";


    // 5. test
    int x;
    std::cin >> x; // 사용자 입력을 받아서 x에 저장

    const int a = x; 
    std::cout << "a = " << a << "\n";

    // constexpr int b = x;  
    // std::cout << "b = " << b << "\n"; // 컴파일 에러: x는 런타임 값이므로 b는 컴파일 시점에 계산할 수 없음

    // 5. test2
    const int y = 10;
    const int b = y; 
    std::cout << "b = " << b << "\n"; // b는 컴파일 시점에 계산 가능

    constexpr int z = 10;
    constexpr int c = z;
    std::cout << "c = " << c << "\n"; // c도 컴파일 시점에 계산 가능

    // 6. test3 - constexpr 함수 d2r에 "런타임 값"을 넣으면 일반 함수처럼 동작
    double user_deg;
    std::cout << "각도를 입력하세요: ";
    std::cin >> user_deg;  // 이 값은 프로그램을 실행해야만 알 수 있음 (런타임 값)

    // d2r은 constexpr 함수지만, user_deg가 런타임 값이라
    // 컴파일 시점에는 계산할 수 없고 프로그램 실행 중에 계산됨
    // -> d2r_normal(user_deg)을 호출한 것과 결과/동작이 동일
    double result = d2r(user_deg);
    std::cout << "d2r(" << user_deg << ") = " << result << "\n";

    return 0;
}
