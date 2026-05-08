#include "data_types.h"
#include <iostream>
#include <string>

// Python은 타입을 자동으로 추론하지만, C++은 명시해야 한다.
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

#ifdef STANDALONE
int main() {
    data_types();
    return 0;
}
#endif