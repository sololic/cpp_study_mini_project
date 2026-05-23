#include "control_flow.h"
#include <iostream>

// ─────────────────────────────────────────
//  조건문 & 반복문
//
//  Python과 구조는 비슷하지만 C++만의 문법이 있다.
// ─────────────────────────────────────────

// 1. switch
void cf_switch() {
    std::cout << "[switch]\n";

    int day = 3;

    switch (day) {
        case 1:
            std::cout << "월요일\n";
            break;
        case 2:
            std::cout << "화요일\n";
            break;
        case 3:
            std::cout << "수요일\n";
            break;
        case 4:
            std::cout << "목요일\n";
            break;
        case 5:
            std::cout << "금요일\n";
            break;
        default:
            std::cout << "주말\n";
            break;
    }

    // break 없는 경우 — fall-through
    std::cout << "\n[fall-through 예시]\n";
    int grade = 2;
    switch (grade) {
        case 1:
        case 2:
        case 3:
            std::cout << "초등학생\n";
            break;
        case 4:
        case 5:
        case 6:
            std::cout << "고학년\n";
            break;
    }

    // Python 비교:
    // Python 3.10+ 에 match-case 있지만 일반적으로 if-elif 사용
    // C++ switch는 정수·문자만 가능 (문자열 불가)
    std::cout << "\n";
}

// 2. do-while — 최소 1번은 실행
void cf_do_while() {
    std::cout << "[do-while]\n";

    int x = 10;
    while (x < 5) {
        std::cout << "while 실행\n";  // 출력 안 됨
    }
    std::cout << "while: 조건이 처음부터 거짓 → 실행 안 됨\n";

    do {
        std::cout << "do-while: 조건이 거짓이어도 최소 1번 실행됨\n";
    } while (x < 5);

    // Python 비교:
    // Python에 do-while 없음
    // Python에서 흉내내기: while True: ... if 조건: break
    std::cout << "\n";
}

// 3. break & continue
void cf_break_continue() {
    std::cout << "[break & continue]\n";

    std::cout << "break: ";
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "continue (짝수만): ";
    for (int i = 0; i < 10; i++) {
        if (i % 2 != 0) continue;
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "\n중첩 break:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 1) break;
            std::cout << "(" << i << "," << j << ") ";
        }
        std::cout << "\n";
    }

    // Python 비교:
    // Python의 break, continue와 동일하게 동작
    std::cout << "\n";
}

#ifdef STANDALONE
int main() {
    cf_switch();
    cf_do_while();
    cf_break_continue();
    return 0;
}
#endif
