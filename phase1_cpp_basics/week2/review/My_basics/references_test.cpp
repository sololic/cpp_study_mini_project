#include <iostream>
#include <string> 
// std::string 사용 위해 추가 현재 환경에서는 안써도 동작 하지만 다른 환경에서는 에러 날 수 있음

// 참조(reference) 기초
void ref_basic() {
    int a = 10;
    int& ref = a;   // ref는 a의 별명
    int b = 15;
    int& ref2 = b;    
     
    /*
            int b = 15;
            int& ref = b;  // error: redeclaration of ‘int& ref’
        references_test.cpp: In function ‘void ref_basic()’:
        references_test.cpp:7:10: error: redeclaration of ‘int& ref’
            7 |     int& ref = b;
            |          ^~~
        references_test.cpp:5:10: note: ‘int& ref’ previously declared here
            5 |     int& ref = a;   // ref는 a의 별명
            |          ^~~
    */

    std::cout << "[참조 기본]\n";
    std::cout << "a = " << a << ", ref = " << ref << "\n";
    std::cout << "b = " << b << ", ref2 = " << ref2 << "\n\n";

    std::cout << "a + b = " << (a + b) << ", ref2 + ref = " << (ref2 + ref) << "\n";
    std::cout << "ref + b = " << (ref + b) << ", a + ref2 = " << (a + ref2) << "\n\n";

    ref = 99;       // ref를 바꾸면 a도 바뀜
    std::cout << "ref = 99 대입 후, a = " << a << "\n";
    ref2 = 88;        // ref2를 바꾸면 b도 바뀜
    std::cout << "ref2 = 88 대입 후, b = " << b << "\n\n";

    std::cout << "a = " << a << ", ref = " << ref << "\n";
    std::cout << "b = " << b << ", ref2 = " << ref2 << "\n\n";

    std::cout << "a + b = " << (a + b) << ", ref2 + ref = " << (ref2 + ref) << "\n";
    std::cout << "ref + b = " << (ref + b) << ", a + ref2 = " << (a + ref2) << "\n\n";
    
    std::cout << std::string(50, '=') << "\n";    
/*
        std::cout << "="*50 << "\n\n";
    references_test.cpp: In function ‘void ref_basic()’:
    references_test.cpp:39:21: error: invalid operands of types ‘const char [2]’ and ‘int’ to binary ‘operator*’
    39 |     std::cout << "="*50 << "\n\n";
        |                  ~~~^~~
        |                  |   |
        |                  |   int
        |                  const char [2]
*/
}

// const 참조
void ref_const() {
    int a = 42;
    const int& cref = a;   // 읽기 전용 참조
    // int& ref = a;   // 일반 참조

    std::cout << "[const 참조]\n";
    std::cout << "cref = " << cref << "\n";

    /*
            // cref = 100;  // 컴파일 에러! const 참조는 변경 불가
        references_test.cpp: In function ‘void ref_const()’:
        references_test.cpp:60:10: error: assignment of read-only reference ‘cref’
        60 |     cref = 100;  // 컴파일 에러! const 참조는 변경 불가
            |     ~~~~~^~~~~
    */

    // const 참조는 리터럴(임시값)도 받을 수 있다
    const int& lit = 100;  // 일반 참조로는 불가능
    std::cout << "리터럴 참조 lit = " << lit << "\n\n";

    /*
        int& ref = 100;  // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
        std::cout << "일반 참조 ref = " << ref << "\n";

        references_test.cpp: In function ‘void ref_const()’:
        references_test.cpp:77:16: error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
        77 |     int& ref = 100;  // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
        |                ^~~
    */
 
    int b = 100;    
    int& ref2 = b;
    std::cout << "일반 참조 ref2 = " << ref2 << "\n";

    
    /*
        **결론**
        일반 참조는 변수에만 붙일 수 있지만, const 참조는 변수뿐 아니라 리터럴(임시값)에도 붙일 수 있다.

        여기서 리터럴(임시값)은 프로그램에서 직접 작성된 고정된 값(예: 숫자 100, 문자열 "hello")을 의미한다. 
        일반 참조는 변수에만 붙일 수 있기 때문에 리터럴에는 사용할 수 없지만, const 참조는 읽기 전용이므로 리터럴에도 사용할 수 있다. 
        why? -> 
        참조는 변수의 별명이라 수정할 수 있어야 함
        But
        일반참조는 "나 이거 바꿀 수도 있어"라고 선언 -> 컴파일러가 거부
        const 참조는 "절대 안 바꿀게"라고 보장 -> 리터럴도 허용

        
        const 참조가 리터럴을 받을 수 있는 이유는, 컴파일러가 리터럴을 임시 변수에 저장하고 그 임시 변수를 const 참조로 연결해주기 때문이다.
        여기서 컴파일러? -> [컴파일러: g++](소스 코드(.cpp)를 컴퓨터가 실행할 수 있는 바이너리로 변환해주는 프로그램)
        ex)
        const int& lit = 100;  // 컴파일러가 내부적으로 임시 변수 temp를 만들어서 temp = 100; const int& lit = temp; 처럼 처리한다.
        ->
        int temp = 100;        // 임시 변수 생성 (자동)
        const int& ref = temp; // 그 임시 변수를 참조
    */

    /*
        ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
        const 참조 vs 일반 참조 — 리터럴 허용 여부
        ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

        ■ 결론
        일반 참조  → 변수에만 가능
        const 참조 → 변수 + 리터럴(임시값) 모두 가능

        ■ 리터럴이란?
        코드에 직접 작성된 고정된 값
        ex) 숫자 100, 문자열 "hello"

        ■ 왜 일반 참조는 리터럴을 못 받나?
        참조 = 변수의 별명 → 수정 가능해야 함
        
        int& ref = 100;  ← "나 이거 바꿀 수도 있어" 선언
                            But 100은 고정값 → 수정 불가
                            → 컴파일러 거부 ❌

        ■ 왜 const 참조는 리터럴을 받을 수 있나?
        const int& ref = 100;  ← "절대 안 바꿀게" 보장
                                    → 컴파일러 허용 ✅

        내부적으로 컴파일러가 자동 처리:
        ┌─────────────────────────────────┐
        │ int temp = 100;       // 임시 변수 생성
        │ const int& ref = temp; // 임시 변수를 참조
        └─────────────────────────────────┘

        ■ 컴파일러란?
        .cpp(사람이 읽는 코드) → 바이너리(컴퓨터가 실행하는 코드)
        로 변환해주는 프로그램
        ex) g++ references_test.cpp -o references_test
    */
}



int main() {
    // ref_basic();
    ref_const();
}