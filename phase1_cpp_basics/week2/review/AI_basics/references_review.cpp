#include "references_review.h"
#include <iostream>

// ─────────────────────────────────────────
//  참조(Reference) 복습
//
//  핵심: 참조는 변수의 "별명(alias)"이다.
//  같은 메모리를 가리키기 때문에 참조를 바꾸면 원본도 바뀐다.
//
//  Python 비유: mutable 객체(list)를 함수에 넘기면 원본이 바뀌는 것과 유사
// ─────────────────────────────────────────

// 1. 기본 참조
void ref_basic() {
    int a = 10;
    int& ref = a;   // ref는 a의 별명

    std::cout << "[참조 기본]\n";
    std::cout << "a = " << a << ", ref = " << ref << "\n";

    ref = 99;       // ref를 바꾸면 a도 바뀜
    std::cout << "ref = 99 대입 후, a = " << a << "\n\n";

    // 주의: 참조는 선언과 동시에 초기화해야 한다
    // int& bad_ref;  // 컴파일 에러!
}

// 2. const 참조 — 읽기만 가능, 원본 변경 불가
void ref_const() {
    int a = 42;
    const int& cref = a;   // 읽기 전용 참조

    std::cout << "[const 참조]\n";
    std::cout << "cref = " << cref << "\n";

    // cref = 100;  // 컴파일 에러! const 참조는 변경 불가

    // const 참조는 리터럴(임시값)도 받을 수 있다
    const int& lit = 100;  // 일반 참조로는 불가능
    std::cout << "리터럴 참조 lit = " << lit << "\n\n";
}

// 3. 참조 vs 값 복사
void ref_vs_copy() {
    int original = 5;

    int copy = original;    // 값 복사 → 별개의 변수
    int& ref  = original;   // 참조   → 같은 변수

    copy = 100;
    ref  = 200;

    std::cout << "[참조 vs 값 복사]\n";
    std::cout << "copy = 100 대입 후, original = " << original << "\n";  // 5 그대로
    std::cout << "ref  = 200 대입 후, original = " << original << "\n\n"; // 200으로 변경
}

// 4. 함수에서 참조 매개변수
void double_value(int& n) {     // 참조로 받으면 원본 변경
    n *= 2;
}

void no_change(int n) {         // 값으로 받으면 복사본만 변경
    n *= 2;
}

void ref_in_function() {
    int x = 10;

    std::cout << "[함수 참조 매개변수]\n";
    no_change(x);
    std::cout << "no_change 후 x = " << x << "\n";   // 10 그대로

    double_value(x);
    std::cout << "double_value 후 x = " << x << "\n\n"; // 20으로 변경
}

#ifdef STANDALONE
int main() {
    ref_basic();
    ref_const();
    ref_vs_copy();
    ref_in_function();
    return 0;
}
#endif
