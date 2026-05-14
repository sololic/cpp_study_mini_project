#include <iostream>
#include <vector>

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  참조(Reference) 문제
//  [Q1~Q3] 함수 본문 작성
//  [Q4~Q5] 버그 수정
// g++ -std=c++17 references_questions.cpp -o ref_q && ./ref_q
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


// [Q1] 두 정수를 참조로 받아서 값을 교환하는 함수를 완성하세요.
// 예시: a=10, b=20 → a=20, b=10
void swap_values(int& a, int& b) {
    // 여기에 작성

}


// [Q2] 정수를 참조로 받아서 n만큼 더해주는 함수를 완성하세요.
// 예시: x=5, n=3 → x=8
void add_n(int& x, int n) {
    // 여기에 작성

}


// [Q3] vector를 const 참조로 받아서 모든 요소의 합을 반환하는 함수를 완성하세요.
// 예시: {1,2,3,4,5} → 15
int sum(const std::vector<int>& v) {
    // 여기에 작성

}


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  [Q4] 버그 수정
//  아래 함수는 x를 3배로 만들려는 의도인데 실행해보면 원본이 안 바뀝니다.
//  왜 그런지 이유를 주석으로 쓰고, 올바르게 수정하세요.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void triple(int n) {
    n *= 3;
}
// 이유:


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  [Q5] 버그 수정
//  아래 함수는 vector에서 최댓값을 0으로 바꾸려는 의도인데
//  실행해보면 원본 벡터가 바뀌지 않습니다.
//  왜 그런지 이유를 주석으로 쓰고, 올바르게 수정하세요.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void clear_max(std::vector<int> v) {
    int max_val = v[0];
    int max_idx = 0;
    for (int i = 1; i < (int)v.size(); i++) {
        if (v[i] > max_val) {
            max_val = v[i];
            max_idx = i;
        }
    }
    v[max_idx] = 0;
}
// 이유:


int main() {
    // Q1 테스트
    int a = 10, b = 20;
    swap_values(a, b);
    std::cout << "[Q1] a=" << a << ", b=" << b << "\n";  // a=20, b=10

    // Q2 테스트
    int x = 5;
    add_n(x, 3);
    std::cout << "[Q2] x=" << x << "\n";  // x=8

    // Q3 테스트
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::cout << "[Q3] sum=" << sum(v) << "\n";  // 15

    // Q4 테스트
    int num = 10;
    triple(num);
    std::cout << "[Q4] num=" << num << "\n";  // 수정 전: 10 / 수정 후: 30

    // Q5 테스트
    std::vector<int> v2 = {3, 7, 1, 9, 4};
    clear_max(v2);
    std::cout << "[Q5] v2: ";
    for (int n : v2) std::cout << n << " ";
    std::cout << "\n";  // 수정 전: 3 7 1 9 4 / 수정 후: 3 7 1 0 4

    return 0;
}
