#include "classes.h"
#include <iostream>
#include <string>

// ─────────────────────────────────────────
//  클래스 기초
//
//  Python의 class와 유사하지만
//  접근 지정자(public/private)를 컴파일러가 강제한다.
// ─────────────────────────────────────────

// 1. 클래스·객체 기초
void cls_basic() {
    std::cout << "[클래스·객체 기초]\n";

    class Dog {
    public:
        std::string name;
        int age;

        void bark() {
            std::cout << name << ": 멍멍!\n";
        }
    };

    Dog d;
    d.name = "바둑이";
    d.age  = 3;
    d.bark();

    // Python: d = Dog(); d.name = "바둑이"
    // C++:    Dog d;     d.name = "바둑이"
    std::cout << "\n";
}

// 2. 생성자·소멸자
void cls_constructor() {
    std::cout << "[생성자·소멸자]\n";

    class Cat {
    public:
        std::string name;

        Cat(std::string n) : name(n) {          // 생성자 — Python __init__
            std::cout << name << " 생성\n";
        }
        ~Cat() {                                 // 소멸자 — Python __del__
            std::cout << name << " 소멸\n";
        }
    };

    Cat c("나비");   // 생성자 호출
    std::cout << c.name << "\n";
    // 함수 끝나면 소멸자 자동 호출

    std::cout << "\n";
}

// 3. 접근 지정자 — public / private
void cls_access() {
    std::cout << "[접근 지정자]\n";

    class BankAccount {
    private:
        int balance;    // 외부에서 직접 접근 불가

    public:
        BankAccount(int b) : balance(b) {}

        void deposit(int amount) { balance += amount; }
        int  getBalance()        { return balance; }
    };

    BankAccount account(1000);
    account.deposit(500);
    std::cout << "잔액: " << account.getBalance() << "\n";
    // account.balance = 9999;  // 에러! private 멤버

    // Python은 _balance 관례로 숨기지만 강제 아님
    // C++은 private이면 컴파일러가 접근 자체를 막음
    std::cout << "\n";
}

// 4. this 포인터
void cls_this() {
    std::cout << "[this 포인터]\n";

    class Counter {
    private:
        int count;

    public:
        Counter(int count) : count(count) {}  // 매개변수명과 멤버명이 같을 때

        void add(int count) {
            this->count += count;  // this->로 멤버 변수 구분
        }

        int get() { return count; }
    };

    Counter c(10);
    c.add(5);
    std::cout << "count: " << c.get() << "\n";  // 15

    // Python: self.count += count
    // C++:    this->count += count
    std::cout << "\n";
}

#ifdef STANDALONE
int main() {
    cls_basic();
    cls_constructor();
    cls_access();
    cls_this();
    return 0;
}
#endif
