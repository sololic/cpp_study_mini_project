#include "polymorphism.h"
#include <iostream>
#include <string>

// ─────────────────────────────────────────
//  다형성
//
//  Python은 기본이 가상 함수 동작
//  C++은 virtual을 명시해야 런타임에 함수가 결정됨
// ─────────────────────────────────────────

// 1. 가상 함수 — virtual
void poly_virtual() {
    std::cout << "[가상 함수]\n";

    class Animal {
    public:
        virtual void sound() {                  // virtual: 런타임에 결정
            std::cout << "...\n";
        }
    };

    class Dog : public Animal {
    public:
        void sound() override {
            std::cout << "멍멍!\n";
        }
    };

    class Cat : public Animal {
    public:
        void sound() override {
            std::cout << "야옹!\n";
        }
    };

    Animal* a1 = new Dog();
    Animal* a2 = new Cat();
    a1->sound();  // 멍멍! — Dog의 sound() 호출
    a2->sound();  // 야옹! — Cat의 sound() 호출

    // virtual 없으면? Animal::sound()가 호출됨 ("...")
    // virtual 있으면? 실제 객체 타입에 맞는 함수 호출

    delete a1;
    delete a2;
    std::cout << "\n";
}

// 2. override — 재정의 명시
void poly_override() {
    std::cout << "[override]\n";

    class Shape {
    public:
        virtual double area() { return 0.0; }
    };

    class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {}
        double area() override {          // override: 컴파일러가 재정의 여부 확인
            return 3.14159 * radius * radius;
        }
    };

    class Rectangle : public Shape {
    private:
        double w, h;
    public:
        Rectangle(double w, double h) : w(w), h(h) {}
        double area() override {
            return w * h;
        }
    };

    Shape* s1 = new Circle(5.0);
    Shape* s2 = new Rectangle(4.0, 3.0);
    std::cout << "원 넓이:     " << s1->area() << "\n";
    std::cout << "직사각형 넓이: " << s2->area() << "\n";

    delete s1;
    delete s2;
    std::cout << "\n";
}

// 3. 순수 가상 함수 & 추상 클래스
void poly_pure_virtual() {
    std::cout << "[순수 가상 함수·추상 클래스]\n";

    class AbstractSensor {   // 추상 클래스 — 직접 객체 생성 불가
    public:
        virtual float read() = 0;          // 순수 가상 함수: = 0
        virtual void  calibrate() = 0;

        void printReading() {              // 일반 함수는 구현 가능
            std::cout << "값: " << read() << "\n";
        }
    };

    class TemperatureSensor : public AbstractSensor {
    public:
        float read()      override { return 23.5f; }
        void  calibrate() override { std::cout << "온도 센서 보정\n"; }
    };

    class PressureSensor : public AbstractSensor {
    public:
        float read()      override { return 101.3f; }
        void  calibrate() override { std::cout << "압력 센서 보정\n"; }
    };

    // AbstractSensor s;  // 에러! 순수 가상 함수가 있으면 객체 생성 불가
    TemperatureSensor ts;
    PressureSensor    ps;

    ts.calibrate();
    ts.printReading();
    ps.calibrate();
    ps.printReading();

    // Python: ABC + @abstractmethod로 동일하게 구현
    // C++: = 0 으로 순수 가상 함수 선언
    std::cout << "\n";
}

#ifdef STANDALONE
int main() {
    poly_virtual();
    poly_override();
    poly_pure_virtual();
    return 0;
}
#endif
