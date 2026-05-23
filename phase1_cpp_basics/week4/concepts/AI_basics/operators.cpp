#include "operators.h"
#include <iostream>

// ─────────────────────────────────────────
//  연산자 심화
//
//  Python과 문법이 같아 보여도 동작이 다른 것들이 있다.
// ─────────────────────────────────────────

// 1. 정수 나눗셈
void op_integer_division() {
    std::cout << "[정수 나눗셈]\n";

    int a = 7, b = 2;

    std::cout << "7 / 2  = " << a / b         << "\n";  // 3  (소수점 버림)
    std::cout << "7 % 2  = " << a % b         << "\n";  // 1  (나머지)
    std::cout << "-7 / 2 = " << -a / b        << "\n";  // -3 (0 방향으로 버림)
    std::cout << "-7 % 2 = " << -a % b        << "\n";  // -1

    // Python 비교:
    // Python: 7 / 2  = 3.5   (항상 float)
    // Python: 7 // 2 = 3     (정수 나눗셈, C++의 / 와 동일)
    // Python: -7 // 2 = -4   (음수 방향으로 내림, C++과 다름!)
    std::cout << "\n";
}

// 2. 증감 연산자 ++ / --
void op_increment() {
    std::cout << "[++ / -- 연산자]\n";

    int x = 5;

    // 전위 증감: 먼저 증가 후 사용
    std::cout << "x = 5\n";
    std::cout << "++x = " << ++x << "\n";  // 6 (먼저 증가)
    std::cout << "x   = " << x   << "\n";  // 6

    x = 5;
    // 후위 증감: 먼저 사용 후 증가
    std::cout << "x = 5\n";
    std::cout << "x++ = " << x++ << "\n";  // 5 (먼저 사용)
    std::cout << "x   = " << x   << "\n";  // 6 (이후 증가)

    // Python 비교:
    // Python에는 ++, -- 없음
    // Python: x += 1  (C++: x++ 또는 ++x)
    std::cout << "\n";
}

// 3. 삼항 연산자
void op_ternary() {
    std::cout << "[삼항 연산자]\n";

    int a = 10, b = 20;

    // 조건 ? 참일 때 값 : 거짓일 때 값
    int max = (a > b) ? a : b;
    std::cout << "max(10, 20) = " << max << "\n";  // 20

    // Python 비교:
    // Python: max = a if a > b else b
    // C++:    max = (a > b) ? a : b
    std::cout << "\n";
}

// 4. 비트 연산자
void op_bitwise() {
    std::cout << "[비트 연산자]\n";

    int a = 0b1010;  // 10
    int b = 0b1100;  // 12

    std::cout << "a      = " << a        << " (1010)\n";
    std::cout << "b      = " << b        << " (1100)\n";
    std::cout << "a & b  = " << (a & b)  << " (1000) AND\n";
    std::cout << "a | b  = " << (a | b)  << " (1110) OR\n";
    std::cout << "a ^ b  = " << (a ^ b)  << " (0110) XOR\n";
    std::cout << "~a     = " << (~a)     << "       NOT\n";
    std::cout << "a << 1 = " << (a << 1) << " (10100) 왼쪽 시프트 (x2)\n";
    std::cout << "a >> 1 = " << (a >> 1) << " (0101)  오른쪽 시프트 (/2)\n";

    int sensors = 0b0000;
    sensors |= 0b0001;  // 전방 센서 ON
    sensors |= 0b0100;  // 좌측 센서 ON
    std::cout << "\n센서 상태: " << sensors << " (전방+좌측 ON)\n\n";
}

#ifdef STANDALONE
int main() {
    op_integer_division();
    op_increment();
    op_ternary();
    op_bitwise();
    return 0;
}
#endif
