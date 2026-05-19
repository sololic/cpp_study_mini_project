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
            break;  // break 없으면 다음 case로 계속 실행됨!
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
        default:  // 해당하는 case 없을 때 (Python의 else)
            std::cout << "주말\n";
            break;
    }

    // break 없는 경우 — fall-through (의도적으로 쓰기도 함)
    std::cout << "\n[fall-through 예시]\n";
    int grade = 2;
    switch (grade) {
        case 1:
        case 2:
        case 3:
            std::cout << "초등학생\n";  // 1, 2, 3 모두 여기로
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

    // while: 조건 먼저 확인 → 처음부터 거짓이면 실행 안 됨
    int x = 10;
    while (x < 5) {
        std::cout << "while 실행\n";  // 출력 안 됨
    }
    std::cout << "while: 조건이 처음부터 거짓 → 실행 안 됨\n";

    // do-while: 일단 실행 → 그 다음 조건 확인
    do {
        std::cout << "do-while: 조건이 거짓이어도 최소 1번 실행됨\n";
    } while (x < 5);  // 거짓이지만 이미 실행된 후

    // 실전 활용: 사용자 입력 검증
    // do {
    //     std::cin >> input;
    // } while (input < 0);  // 올바른 값 입력할 때까지 반복

    // Python 비교:
    // Python에 do-while 없음
    // Python에서 흉내내기: while True: ... if 조건: break
    std::cout << "\n";
}

// 3. break & continue
void cf_break_continue() {
    std::cout << "[break & continue]\n";

    // break: 반복문 즉시 탈출
    std::cout << "break: ";
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;  // i가 5가 되면 탈출
        std::cout << i << " ";
    }
    std::cout << "\n";  // 0 1 2 3 4

    // continue: 이번 반복만 건너뜀
    std::cout << "continue (짝수만): ";
    for (int i = 0; i < 10; i++) {
        if (i % 2 != 0) continue;  // 홀수면 건너뜀
        std::cout << i << " ";
    }
    std::cout << "\n";  // 0 2 4 6 8

    // 중첩 반복문에서 break는 가장 안쪽만 탈출
    std::cout << "\n중첩 break:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 1) break;  // 안쪽 for만 탈출
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
