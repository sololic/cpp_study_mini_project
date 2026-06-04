# Week 6 — 클래스·상속·다형성

Part 04 (클래스) + Part 08·09·10 (상속·다형성) 기반 학습.  
개념 학습 → 문제 풀이 → 스터디 설명 순서로 진행.

> 이전 내용 → [week5/README.md](../week5/README.md)

---

## 📊 학습 진행 현황

| 상태 | 개념 | 세부 내용 |
|:---:|------|-----------|
| ⬜ | 클래스 기초 | 클래스·객체, 생성자·소멸자, 접근 지정자, `this` |
| ⬜ | 상속 | 기반·파생 클래스, 접근 지정자 상속, 생성자 호출 순서 |
| ⬜ | 다형성 | 가상 함수, `override`, 순수 가상 함수, 추상 클래스 |

### 문제 풀이

| 상태 | 주제 |
|:---:|------|
| ⬜ | 클래스 기초 문제 |
| ⬜ | 상속 문제 |
| ⬜ | 다형성 문제 |

> ⬜ 미완료 / ✅ 완료

---

## 📁 파일 구조

```
week5/
├── concepts/
│   ├── AI_basics/
│   │   ├── main.cpp                ← 전체 실행 진입점
│   │   ├── classes.cpp/h           ← 클래스 기초 (생성자, 소멸자, 접근 지정자, this)
│   │   ├── inheritance.cpp/h       ← 상속 (기반·파생 클래스, 생성자 호출 순서)
│   │   └── polymorphism.cpp/h      ← 다형성 (가상 함수, override, 순수 가상 함수)
│   └── My_basics/      ← 직접 작성한 실습 코드
├── questions/          ← 문제 풀이
├── docs/               ← 개념 정리 md
└── README.md
```

---

## 📅 학습 내용

### 1. 클래스 기초 (Part 04)

| 주제 | 내용 | Python과 차이 |
|------|------|--------------|
| 클래스·객체 | 데이터 + 함수 묶기 | Python `class`와 유사 |
| 생성자·소멸자 | 객체 생성/소멸 시 자동 호출 | Python `__init__` / `__del__` |
| 접근 지정자 | `public`, `private`, `protected` | Python `_` 관례와 다름 (컴파일러가 강제) |
| `this` 포인터 | 현재 객체를 가리키는 포인터 | Python `self`와 유사 |

### 2. 상속 (Part 08·09)

| 주제 | 내용 | Python과 차이 |
|------|------|--------------|
| 기반·파생 클래스 | `class Dog : public Animal` | Python `class Dog(Animal)` |
| 접근 지정자 상속 | `public` / `protected` / `private` 상속 | Python에 없음 |
| 생성자 호출 순서 | 기반 클래스 먼저, 파생 클래스 나중 | Python `super().__init__()` |

### 3. 다형성 (Part 10)

| 주제 | 내용 | Python과 차이 |
|------|------|--------------|
| 가상 함수 | `virtual` — 런타임에 함수 결정 | Python은 기본이 가상 함수 |
| `override` | 파생 클래스에서 재정의 명시 | Python에 없음 |
| 순수 가상 함수 | `= 0` — 반드시 재정의 강제 | Python `ABC` / `abstractmethod` |
| 추상 클래스 | 순수 가상 함수가 하나라도 있으면 | Python `ABC` |

---

## ⚙️ 빌드 & 실행

```bash
cd concepts/AI_basics
mkdir -p build

# 전체 실행
g++ -std=c++17 main.cpp classes.cpp inheritance.cpp polymorphism.cpp -o build/week5 && ./build/week5

# 주제별 단독 실행
g++ -std=c++17 -DSTANDALONE classes.cpp -o build/cls && ./build/cls
g++ -std=c++17 -DSTANDALONE inheritance.cpp -o build/inh && ./build/inh
g++ -std=c++17 -DSTANDALONE polymorphism.cpp -o build/poly && ./build/poly
```
