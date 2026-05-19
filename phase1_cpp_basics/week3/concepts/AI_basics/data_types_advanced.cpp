#include "data_types_advanced.h"
#include <iostream>

// ─────────────────────────────────────────
//  자료형 심화
//
//  Python은 자료형을 자동으로 관리하지만
//  C++은 개발자가 직접 선택하고 관리해야 한다.
// ─────────────────────────────────────────

// 1. sizeof — 자료형이 메모리를 얼마나 차지하는지
void types_sizeof() {
    std::cout << "[sizeof — 자료형 크기]\n";
    std::cout << "bool   : " << sizeof(bool)   << " byte\n";  // 1
    std::cout << "char   : " << sizeof(char)   << " byte\n";  // 1
    std::cout << "int    : " << sizeof(int)    << " bytes\n"; // 4
    std::cout << "long   : " << sizeof(long)   << " bytes\n"; // 4 or 8
    std::cout << "float  : " << sizeof(float)  << " bytes\n"; // 4
    std::cout << "double : " << sizeof(double) << " bytes\n"; // 8

    // Python은 int 크기 제한 없음 (자동 확장)
    // C++은 int = 4bytes → 최대 약 21억까지만 저장 가능
    std::cout << "\n";
}

// 2. auto — 타입 자동 추론
void types_auto() {
    std::cout << "[auto — 타입 자동 추론]\n";

    auto a = 10;        // int로 추론
    auto b = 3.14;      // double로 추론
    auto c = true;      // bool로 추론
    auto d = 'A';       // char로 추론

    std::cout << "auto a = 10    → sizeof: " << sizeof(a) << " bytes (int)\n";
    std::cout << "auto b = 3.14  → sizeof: " << sizeof(b) << " bytes (double)\n";
    std::cout << "auto c = true  → sizeof: " << sizeof(c) << " byte  (bool)\n";
    std::cout << "auto d = 'A'   → sizeof: " << sizeof(d) << " byte  (char)\n";

    // Python처럼 타입 명시 안 해도 되지만
    // 초기화 없이는 사용 불가
    // auto x;  // 에러! 초기값 없으면 추론 불가
    std::cout << "\n";
}

// 3. 타입 변환 — 암시적 vs 명시적
void types_conversion() {
    std::cout << "[타입 변환]\n";

    // 암시적 변환 (자동): 작은 타입 → 큰 타입은 안전
    int    i = 10;
    double d = i;   // int → double 자동 변환 (데이터 손실 없음)
    std::cout << "int → double: " << d << "\n";

    // 암시적 변환 (위험): 큰 타입 → 작은 타입은 데이터 손실
    double pi = 3.14159;
    int    n  = pi;   // double → int: 소수점 버림!
    std::cout << "double → int (암시적): " << n << "  ← 소수점 손실!\n";

    // 명시적 변환 (캐스팅): 의도를 명확히 표현
    int x = 7, y = 2;
    double result = (double)x / y;   // C 스타일 캐스팅
    std::cout << "7 / 2 (int)    = " << x / y  << "\n";  // 3 (정수 나눗셈)
    std::cout << "7 / 2 (double) = " << result << "\n";  // 3.5

    // Python 비교:
    // Python: 7 / 2 = 3.5 (자동으로 float)
    // C++:    7 / 2 = 3   (정수 나눗셈, 소수점 버림)
    std::cout << "\n";
}

// 4. 오버플로우 — 자료형 범위 초과
void types_overflow() {
    std::cout << "[오버플로우]\n";

    // int 최댓값: 2,147,483,647 (약 21억)
    int max_int = 2147483647;
    std::cout << "int 최댓값     : " << max_int     << "\n";
    std::cout << "최댓값 + 1     : " << max_int + 1 << "\n";  // 음수로 바뀜!

    // unsigned int: 음수 없음, 0 ~ 4,294,967,295
    unsigned int u = 0;
    std::cout << "unsigned 0 - 1 : " << u - 1 << "\n";  // 엄청 큰 수로 바뀜!

    // Python은 자동으로 큰 정수 타입으로 확장 → 오버플로우 없음
    // C++은 범위 초과 시 예상치 못한 값 → 버그의 원인!
    std::cout << "\n";
}

// 5. const & constexpr
void types_const() {
    std::cout << "[const & constexpr]\n";

    // const: 런타임에 값이 정해지는 상수
    const int MAX_SIZE = 100;
    // MAX_SIZE = 200;  // 에러! 변경 불가

    // constexpr: 컴파일 타임에 값이 정해지는 상수 (더 엄격)
    constexpr double PI = 3.14159265;
    // constexpr은 컴파일 중에 값이 확정되어 최적화에 유리

    std::cout << "MAX_SIZE = " << MAX_SIZE << "\n";
    std::cout << "PI       = " << PI       << "\n";

    // Python 비교:
    // Python에는 진짜 상수 없음 (관례상 대문자로 쓰지만 변경 가능)
    // C++의 const는 컴파일러가 변경을 막아줌
    std::cout << "\n";
}

#ifdef STANDALONE
int main() {
    types_sizeof();
    types_auto();
    types_conversion();
    types_overflow();
    types_const();
    return 0;
}
#endif
