#include <iostream>
#include <vector>

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  포인터(Pointer) 문제
//  [Q1~Q3] 함수 본문 작성
//  [Q4~Q5] 버그 수정
// g++ -std=c++17 pointers_questions.cpp -o ptr_q && ./ptr_q
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


// [Q1] 두 정수의 포인터를 받아서 값을 교환하는 함수를 완성하세요.
// 예시: a=10, b=20 → a=20, b=10
void swap_ptr(int* a, int* b) {
    // 여기에 작성 

}


// [Q2] 포인터를 받아서 nullptr이 아니면 값을 2배로 바꾸고
// nullptr이면 "null pointer" 를 출력하는 함수를 완성하세요.
void safe_double(int* p) {
    // 여기에 작성

}


// [Q3] 정수 배열과 크기를 받아서 최솟값의 포인터를 반환하는 함수를 완성하세요.
// 예시: {5,2,8,1,9} → 1을 가리키는 포인터
int* find_min(int* arr, int size) {
    // 여기에 작성

}


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  [Q4] 버그 수정
//  아래 함수는 포인터가 가리키는 값을 출력하려는 의도인데
//  실행하면 프로그램이 크래시 납니다.
//  왜 그런지 이유를 주석으로 쓰고, 올바르게 수정하세요.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void print_value(int* p) {
    std::cout << "값: " << *p << "\n";
}
// 이유:

// 버그를 발생시키는 호출 예시 (main에서 확인):
// int* ptr = nullptr;
// print_value(ptr);  // 크래시!


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  [Q5] 버그 수정
//  아래 함수는 포인터로 값을 10으로 바꾸려는 의도인데
//  컴파일 에러가 납니다.
//  왜 그런지 이유를 주석으로 쓰고, 올바르게 수정하세요.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void set_ten(const int* p) {
    *p = 10;
}
// 이유:


int main() {
    // Q1 테스트
    int a = 10, b = 20;
    swap_ptr(&a, &b);
    std::cout << "[Q1] a=" << a << ", b=" << b << "\n";  // a=20, b=10

    // Q2 테스트
    int x = 5;
    safe_double(&x);
    std::cout << "[Q2] x=" << x << "\n";  // x=10
    safe_double(nullptr);                  // "null pointer" 출력

    // Q3 테스트
    int arr[] = {5, 2, 8, 1, 9};
    int* min_ptr = find_min(arr, 5);
    std::cout << "[Q3] min=" << *min_ptr << "\n";  // 1

    // Q4 테스트
    int* ptr = nullptr;
    print_value(ptr);  // 수정 전: 크래시 / 수정 후: 안전하게 처리

    // Q5 테스트
    int num = 5;
    set_ten(&num);
    std::cout << "[Q5] num=" << num << "\n";  // 수정 후: 10

    return 0;
}
