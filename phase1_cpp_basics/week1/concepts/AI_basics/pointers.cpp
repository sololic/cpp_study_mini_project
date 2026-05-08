#include "pointers.h"
#include <iostream>

// 포인터(*): 변수의 메모리 주소를 저장.
// &var  → var의 주소
// *ptr  → ptr이 가리키는 값 (역참조)
void pointers() {
    int  val = 42;
    int* ptr = &val;

    std::cout << "[포인터]\n";
    std::cout << "val 값: "       << val  << "\n";
    std::cout << "val 주소: "     << ptr  << "\n";
    std::cout << "역참조(*ptr): " << *ptr << "\n";

    *ptr = 100;
    std::cout << "변경 후 val: " << val << "\n\n";
}

#ifdef STANDALONE
int main() {
    pointers();
    return 0;
}
#endif