#include "references.h"
#include <iostream>

// 참조(&)는 변수의 별명(alias). 원본을 직접 수정한다.
// Python의 list 같은 mutable 객체를 넘기는 것과 유사한 효과.
void add_ten(int& n) {
    n += 10;
}

void references() {
    int x = 5;
    add_ten(x);
    std::cout << "[참조] x = " << x << "\n\n";  // 15
}

#ifdef STANDALONE
int main() {
    references();
    return 0;
}
#endif