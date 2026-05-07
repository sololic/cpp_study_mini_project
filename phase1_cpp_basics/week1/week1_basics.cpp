// ============================================================
//  Week 1 — C++ 기초 문법 (Python 개발자 관점)
//  주제: 자료형 / 입출력 / 참조 / 포인터 / 함수 / vector
// ============================================================

#include <iostream>
#include <vector>
#include <string>

// ──────────────────────────────────────────
//  1. 자료형 (Data Types)
// ──────────────────────────────────────────
// Python은 타입을 자동으로 추론하지만, C++은 명시해야 한다.
//
//  Python:  x = 10
//  C++:     int x = 10;
void data_types() {
    int    a = 10;
    double b = 3.14;
    bool   c = true;
    char   d = 'A';
    std::string s = "hello";

    std::cout << "[자료형]\n";
    std::cout << "int: "    << a << "\n";
    std::cout << "double: " << b << "\n";
    std::cout << "bool: "   << c << "\n";
    std::cout << "char: "   << d << "\n";
    std::cout << "string: " << s << "\n\n";
}

// ──────────────────────────────────────────
//  2. 참조 (Reference)
// ──────────────────────────────────────────
// 참조(&)는 변수의 별명(alias). 원본을 직접 수정한다.
// Python의 list 같은 mutable 객체를 넘기는 것과 유사한 효과.
void add_ten(int& n) {   // &: 참조로 받음 → 원본 변경
    n += 10;
}

void references() {
    int x = 5;
    add_ten(x);           // x 자체가 변경됨
    std::cout << "[참조] x = " << x << "\n\n";  // 15
}

// ──────────────────────────────────────────
//  3. 포인터 (Pointer)
// ──────────────────────────────────────────
// 포인터(*): 변수의 메모리 주소를 저장.
// &var  → var의 주소
// *ptr  → ptr이 가리키는 값 (역참조)
void pointers() {
    int  val = 42;
    int* ptr = &val;      // ptr에 val의 주소 저장

    std::cout << "[포인터]\n";
    std::cout << "val 값: "    << val  << "\n";
    std::cout << "val 주소: "  << ptr  << "\n";
    std::cout << "역참조(*ptr): " << *ptr << "\n";

    *ptr = 100;           // 포인터로 원본 값 변경
    std::cout << "변경 후 val: " << val << "\n\n";
}

// ──────────────────────────────────────────
//  4. std::vector (동적 배열)
// ──────────────────────────────────────────
// Python의 list와 거의 같다.
//  Python:  nums = [1, 2, 3];  nums.append(4)
//  C++:     vector<int> nums = {1,2,3};  nums.push_back(4);
void vectors() {
    std::vector<int> nums = {1, 2, 3};
    nums.push_back(4);    // append

    std::cout << "[vector] ";
    for (int n : nums) {  // Python의 for n in nums: 와 동일
        std::cout << n << " ";
    }
    std::cout << "\n";
    std::cout << "크기: " << nums.size() << "\n\n";
}

// ──────────────────────────────────────────
//  main
// ──────────────────────────────────────────
int main() {
    data_types();
    references();
    pointers();
    vectors();
    return 0;
}
/*
여러줄 
주석
입니다
*/
// ──────────────────────────────────────────
//  빌드 & 실행 방법
//  g++ -std=c++17 week1_basics.cpp -o week1_basics
//  ./week1_basics
// ──────────────────────────────────────────
