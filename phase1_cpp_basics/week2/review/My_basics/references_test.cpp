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

    int b = 100;
    int& ref = 100;  // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    std::cout << "일반 참조 ref = " << ref << "\n";
    
    int& ref2 = b;
    std::cout << "일반 참조 ref2 = " << ref2 << "\n";
}

int main() {
    // ref_basic();
    ref_const();
}