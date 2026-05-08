#include <iostream>

int main() {
    std::cout << "Hello, C++!\n";
    return 0;
}

/*
-> 
#include <iostream> 안넣고 했을때 나오는 에러
<iostream>: C++에서 표준 입출력 스트림을 제공하는 라이브러리.

1_test_study.cpp: In function ‘int main()’:
1_test_study.cpp:2:10: error: ‘cout’ is not a member of ‘std’
    2 |     std::cout << "Hello, C++!\n";
      |          ^~~~
1_test_study.cpp:1:1: note: ‘std::cout’ is defined in header ‘<iostream>’; this is probably fixable by adding ‘#include <iostream>’
  +++ |+#include <iostream>
    1 | int main() {
*/