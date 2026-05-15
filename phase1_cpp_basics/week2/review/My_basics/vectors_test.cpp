// #include "vectors_review.h"
#include <iostream>
#include <vector>
#include <algorithm>   // sort, find

// ─────────────────────────────────────────
//  std::vector (동적배열) 복습
//
//  Python의 list와 거의 동일하다.
//  크기가 자동으로 늘어나고 줄어든다.
// ─────────────────────────────────────────

// 1. 기본 operations
void vec_basic() {
    std::cout << "[vector 기본]\n";
    std::vector<int> v = {1, 2, 3};

    v.push_back(4);     // 뒤에 추가 (Python: append)
    std::cout << "마지막: "  << v.back()  << "\n";   
    v.pop_back();       // 뒤에서 제거 (Python: pop)
    std::cout << "마지막: "  << v.back()  << "\n";
    
    std::cout << "크기: "    << v.size()  << "\n";   // 3
    std::cout << "비어있나: " << v.empty() << "\n";   // 0 (false)
    std::cout << "첫 번째: " << v.front() << "\n";   // 1
    std::cout << "마지막: "  << v.back()  << "\n";   // 3

    // 인덱싱
    std::cout << "v[1] = "   << v[1]    << "\n";   // 2 (범위 체크 없음)
    std::cout << "v.at(1) = "<< v.at(1) << "\n\n"; // 2 (범위 초과 시 예외 발생)

    // std::cout << "v[3] = "   << v[3]    << "\n";   // 2 (범위 체크 없음)
    // std::cout << "v.at(3) = "<< v.at(3) << "\n\n"; // 2 (범위 초과 시 예외 발생)

}

// 2. 반복문 3가지
void vec_loop() {
    std::vector<int> v = {10, 20, 30, 40};

    std::cout << "[반복문]\n";

    // (1) range-for — 가장 간단 (Python: for n in v)
    std::cout << "range-for: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    // (2) 인덱스 - (python for i in range(len(v)))
    std::cout << "인덱스:    ";
    for (int i = 0; i < (int)v.size(); i++) std::cout << v[i] << " ";
    std::cout << "\n";

    // (3) range-for 참조 — 값을 바꾸고 싶을 때
    for (int& n : v) n *= 2;   // 모든 요소 2배
    std::cout << "2배 후:    ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n\n";
}

// 3. 자주 쓰는 수정 operations
void vec_modify() {
    std::vector<int> v = {5, 2, 8, 1, 9, 3};

    std::cout << "[vector 수정]\n";

    // 정렬
    // v.begin()  // 첫 번째 요소를 가리킴
    // v.end()    // 마지막 요소 다음을 가리킴 (마지막 아님!)
    std::cout << *v.begin() << "\n";   // 첫 번째 값 출력
    std::cout << *(v.end()-1) << "\n"; // 마지막 값 출력

    std::sort(v.begin(), v.end()); 
    // 어디부터 어디까지 정렬할지" 범위 
    // 여기서 왜 (v.end()-1)이 아니라 v.end()인지?
    // -> sort는 python의 슬라이스와 같이 마지막 요소의 -1 범위까지 정렬
    std::cout << "정렬 후: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    // 검색
    auto it = std::find(v.begin(), v.end(), 8);
    if (it != v.end())
        std::cout << "8 찾음, 인덱스: " << (it - v.begin()) << "\n";

    // 중간 삽입 / 삭제
    v.insert(v.begin() + 2, 99);   // 인덱스 2에 99 삽입
    std::cout << "세 번째: " << v.at(2) << "\n"; // at : 인덱스
    /*
    Why v[2] 대신 v.at(2)인가?
    v[10]    // 멈출 수도 있고, 이상한 값 출력하고 그냥 계속 실행될 수도 있음
         // → 어디서 문제인지 찾기 어려움 (undefined behavior)

    v.at(10) // 무조건 여기서 멈추고 에러 메시지 출력
            // → "out_of_range" 라고 정확히 알려줌
    */
    v.erase(v.begin() + 2);        // 인덱스 2 삭제
    
    /* 문제
        v.insert(v.at(2), 99);   
        v.erase(v.at(2));         
    */

    /*
        v.insert(v.at(2), 99);   // 에러!
        v.insert(v.begin()+2, 99); // OK: 인덱스 2 위치에 99 삽입

        v.erase(v.at(2));          // 에러!
        v.erase(v.begin()+2);      // OK: 인덱스 2 삭제
    */

    // 전체 삭제
    v.clear();
    std::cout << "clear 후 크기: " << v.size() << "\n\n";
}

// 4. 2D vector
void vec_2d() {
    // 3x3 행렬, 0으로 초기화
    std::vector<std::vector<int>> mat(3, std::vector<int>(3, 0));

    /*
    mat = 변수명(필수로 선언해줘야함 이름은 변경 가능)
    mat = [[0]*3 for _ in range(3)]
    # mat이라는 이름으로 2D 리스트 선언

    std::vector<int>(3, 0)
    // int형 vector를 크기 3, 전부 0으로 초기화
    // → {0, 0, 0}

    std::vector<std::vector<int>> mat(3, std::vector<int>(3, 0));
    // {0,0,0} 짜리 vector를 3개 만든 vector
    // → { {0,0,0}, {0,0,0}, {0,0,0} }
    */

    mat[0][0] = 1;
    mat[1][1] = 2;
    mat[2][2] = 3;

    std::cout << "[2D vector]\n";
    for (auto& row : mat) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
    
    /* python
    for row in mat:
    for val in row:
        print(val, end=" ")
    print()
    */
}

// #ifdef STANDALONE
int main() {
    vec_basic();
    vec_loop();
    vec_modify();
    vec_2d();
    return 0;
}
// #endif
