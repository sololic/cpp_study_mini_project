#include "pointers_review.h"
#include <iostream>

// ─────────────────────────────────────────
//  포인터(Pointer) 처음부터 다시
//
//  핵심: 포인터는 "메모리 주소를 저장하는 변수"다.
//
//  메모리를 집으로 비유하면:
//  - 변수  = 집 안에 있는 물건
//  - 주소  = 집 주소 (0x7fff...)
//  - 포인터 = 집 주소가 적힌 메모지
//  - 역참조 = 메모지의 주소로 찾아가서 물건을 꺼냄
// ─────────────────────────────────────────

// 1. 포인터 기본
void ptr_basic() {
    int val = 42;
    int* ptr = &val;   // &val: val의 주소 / int*: 주소를 담는 포인터 변수

    std::cout << "[포인터 기본]\n";
    std::cout << "val        = " << val  << "\n";    // 42  (값)
    std::cout << "&val (주소) = " << &val << "\n";   // 0x7fff... (주소)
    std::cout << "ptr        = " << ptr  << "\n";    // 0x7fff... (주소, &val과 동일)
    std::cout << "*ptr (역참조)= " << *ptr << "\n";  // 42  (ptr이 가리키는 값)

    *ptr = 100;        // 역참조로 원본 값 변경
    std::cout << "*ptr = 100 후, val = " << val << "\n\n";

    // 정리
    // &val  → val의 주소를 가져옴 (주소 연산자)
    // int*  → 주소를 저장하는 포인터 타입 선언
    // *ptr  → ptr이 가리키는 주소의 값 (역참조 연산자)
}

// 2. nullptr — 포인터의 초기값
void ptr_nullptr() {
    int* ptr = nullptr;   // 아무것도 가리키지 않는 포인터
    int val = 42;
    ptr = &val;
    std::cout << "[nullptr]\n";
    std::cout << "ptr = " << ptr << "\n";   // 0x0
    std::cout << "*ptr = " << *ptr << "\n";   // 0x0
    std::cout << "val = " << val << "\n";   // 0x0    
    std::cout << "&val = " << &val << "\n";   // 0x0  
    * ptr = 99;  // val이 99로 변경됨

    std::cout << "ptr = " << ptr << "\n";   // 0x0
    std::cout << "*ptr = " << *ptr << "\n";   // 0x0
    std::cout << "val = " << val << "\n";   // 0x0
    std::cout << "&val = " << &val << "\n";   // 0x0

    // *ptr = 10;  // 위험! nullptr 역참조 → 프로그램 크래시(Segmentation fault)
    // std::cout << "ptr = " << ptr << "\n"; 
    // 포인터 사용 전 nullptr 체크가 중요하다
    if (ptr != nullptr) {
        std::cout << *ptr << "\n";
    } else {
        std::cout << "ptr이 nullptr — 역참조 안 함\n\n";
    }
}

// 3. 포인터 vs 참조
void ptr_vs_ref() {
    int a = 10;

    int* ptr = &a;   // 포인터: 주소 저장, 나중에 다른 변수 가리킬 수 있음
    int& ref = a;    // 참조:   별명, 항상 a만 가리킴

    std::cout << "[포인터 vs 참조]\n";

    *ptr = 20;       // 포인터로 값 변경
    std::cout << "포인터로 변경 후 a = " << a << "\n";

    ref = 30;        // 참조로 값 변경
    std::cout << "참조로 변경 후  a = " << a << "\n";

    int b = 99;
    ptr = &b;        // 포인터는 다른 변수로 재지정 가능
    // int& ref2 = b; 는 가능하지만 ref = b 는 재지정이 아니라 값 복사
    std::cout << "ptr을 b로 변경 후 *ptr = " << *ptr << "\n\n";

    // 요약
    // 포인터: 주소 저장, 재지정 가능, nullptr 가능
    // 참조:   별명,     재지정 불가, nullptr 없음 (항상 유효)
}

// 4. const 포인터 — 헷갈리는 부분
void ptr_const() {
    int a = 10;
    int b = 20;

    // (1) 가리키는 값을 못 바꿈 (포인터 자체는 이동 가능)
    const int* p1 = &a;
    // *p1 = 99;   // 에러! 값 변경 불가
    p1 = &b;       // OK: 다른 변수 가리키기 가능

    // (2) 포인터 자체를 못 바꿈 (값은 변경 가능)
    int* const p2 = &a;
    *p2 = 99;      // OK: 값 변경 가능
    // p2 = &b;    // 에러! 포인터 재지정 불가

    // (3) 둘 다 못 바꿈
    const int* const p3 = &a;
    // *p3 = 1;    // 에러!
    // p3 = &b;    // 에러!

    std::cout << "[const 포인터]\n";
    std::cout << "a = " << a << ", *p2 = 99로 변경됨\n\n";

    // 읽는 법: * 기준으로 const 위치 확인
    // const int* p  →  *p가 const  →  값 변경 불가
    // int* const p  →  p가 const   →  재지정 불가
}

#ifdef STANDALONE
int main() {
    // ptr_basic();
    ptr_nullptr();
    // ptr_vs_ref();
    // ptr_const();
    return 0;
}
#endif
