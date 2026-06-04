#include "inheritance.h"
#include <iostream>
#include <string>

// ─────────────────────────────────────────
//  상속
//
//  Python: class Dog(Animal)
//  C++:    class Dog : public Animal
// ─────────────────────────────────────────

// 1. 상속 기초
void inh_basic() {
    std::cout << "[상속 기초]\n";

    class Animal {
    public:
        std::string name;
        Animal(std::string n) : name(n) {}

        void eat() {
            std::cout << name << " 먹는 중\n";
        }
    };

    class Dog : public Animal {
    public:
        Dog(std::string n) : Animal(n) {}  // 기반 클래스 생성자 호출

        void bark() {
            std::cout << name << " 멍멍!\n";
        }
    };

    Dog d("바둑이");
    d.eat();   // Animal에서 상속받은 함수
    d.bark();  // Dog 자신의 함수

    // Python: class Dog(Animal): def __init__(self, n): super().__init__(n)
    // C++:    class Dog : public Animal { Dog(n) : Animal(n) {} };
    std::cout << "\n";
}

// 2. 접근 지정자와 상속
void inh_access() {
    std::cout << "[접근 지정자와 상속]\n";

    class Base {
    public:
        int pub = 1;
    protected:
        int pro = 2;   // 파생 클래스에서만 접근 가능
    private:
        int pri = 3;   // 파생 클래스도 접근 불가
    };

    class Derived : public Base {
    public:
        void show() {
            std::cout << "public:    " << pub << "\n";  // OK
            std::cout << "protected: " << pro << "\n";  // OK
            // std::cout << pri;  // 에러! private는 파생 클래스도 접근 불가
        }
    };

    Derived d;
    d.show();
    std::cout << d.pub << "\n";  // OK — public이라 외부에서도 접근 가능
    // d.pro  // 에러! protected는 외부에서 접근 불가

    // Python: private(_) 관례만 있고 컴파일러 강제 없음
    // C++: public/protected/private 구분을 컴파일러가 강제
    std::cout << "\n";
}

// 3. 생성자 호출 순서
void inh_constructor_order() {
    std::cout << "[생성자 호출 순서]\n";

    class Base {
    public:
        Base()  { std::cout << "Base 생성자\n"; }
        ~Base() { std::cout << "Base 소멸자\n"; }
    };

    class Derived : public Base {
    public:
        Derived()  { std::cout << "Derived 생성자\n"; }
        ~Derived() { std::cout << "Derived 소멸자\n"; }
    };

    Derived d;
    // 생성: Base → Derived 순서
    // 소멸: Derived → Base 순서 (반대)
    std::cout << "\n";
}

#ifdef STANDALONE
int main() {
    inh_basic();
    inh_access();
    inh_constructor_order();
    return 0;
}
#endif
