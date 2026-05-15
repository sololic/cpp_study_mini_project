#include <iostream>
#include <vector>
#include <algorithm>

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  vector(동적배열) 문제
//  [Q1~Q3] 함수 본문 작성
//  [Q4~Q5] 버그 수정
// g++ -std=c++17 vectors_questions.cpp -o vec_q && ./vec_q
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


// [Q1] vector에서 짝수만 골라서 새 vector로 반환하는 함수를 완성하세요.
// 예시: {1,2,3,4,5,6} → {2,4,6}
std::vector<int> get_evens(const std::vector<int>& v) {
    // 여기에 작성

}


// [Q2] vector를 받아서 역순으로 출력하는 함수를 완성하세요.
// (vector 자체를 바꾸지 말고 출력만)
// 예시: {1,2,3,4,5} → 5 4 3 2 1
void print_reverse(const std::vector<int>& v) {
    // 여기에 작성

}


// [Q3] 3x3 2D vector를 받아서 대각선 합계를 반환하는 함수를 완성하세요.
// 예시:
// 1 0 0
// 0 2 0  → 대각선 합계: 1+2+3 = 6
// 0 0 3
int diagonal_sum(const std::vector<std::vector<int>>& mat) {
    // 여기에 작성

}


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// [Q4] 버그 수정
// 아래 함수는 앞 3개만 정렬하려는 의도인데 전체가 정렬됩니다.
// 왜 그런지 이유를 주석으로 쓰고, 올바르게 수정하세요.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void sort_first_three(std::vector<int>& v) {
    std::sort(v.begin(), v.end());
}
// 이유:


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// [Q5] 버그 수정
// 아래 함수는 vector의 모든 요소를 2배로 만들려는 의도인데
// 실행해보면 원본이 바뀌지 않습니다.
// 왜 그런지 이유를 주석으로 쓰고, 올바르게 수정하세요.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void double_all(std::vector<int>& v) {
    for (int n : v) n *= 2;
}
// 이유:


int main() {
    // Q1 테스트
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6};
    std::vector<int> evens = get_evens(v1);
    std::cout << "[Q1] 짝수: ";
    for (int n : evens) std::cout << n << " ";
    std::cout << "\n";  // 2 4 6

    // Q2 테스트
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    std::cout << "[Q2] 역순: ";
    print_reverse(v2);
    std::cout << "\n";  // 5 4 3 2 1

    // Q3 테스트
    std::vector<std::vector<int>> mat(3, std::vector<int>(3, 0));
    mat[0][0] = 1; mat[1][1] = 2; mat[2][2] = 3;
    std::cout << "[Q3] 대각선 합: " << diagonal_sum(mat) << "\n";  // 6

    // Q4 테스트
    std::vector<int> v4 = {5, 2, 8, 1, 9, 3};
    sort_first_three(v4);
    std::cout << "[Q4] 앞 3개만 정렬: ";
    for (int n : v4) std::cout << n << " ";
    std::cout << "\n";  // 수정 후: 2 5 8 1 9 3

    // Q5 테스트
    std::vector<int> v5 = {1, 2, 3, 4, 5};
    double_all(v5);
    std::cout << "[Q5] 2배 후: ";
    for (int n : v5) std::cout << n << " ";
    std::cout << "\n";  // 수정 전: 1 2 3 4 5 / 수정 후: 2 4 6 8 10

    return 0;
}
