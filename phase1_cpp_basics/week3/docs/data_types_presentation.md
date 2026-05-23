# 자료형 심화 — 발표 정리

---

## 1. sizeof() — 자료형 메모리 크기 확인

자료형이 메모리를 얼마나 차지하는지 확인하는 함수.  
**자료형 이름**뿐만 아니라 **변수명**도 넣을 수 있다.

```cpp
// 자료형 직접 입력
std::cout << sizeof(int);    // 4
std::cout << sizeof(double); // 8

// 변수명 입력도 가능
int x = 42;
std::cout << sizeof(x);      // 4 (int니까)
```

---

## 2. auto — 타입 자동 추론

초기값을 보고 타입을 자동으로 결정한다. 반드시 `= 값`과 함께 써야 한다.

```cpp
auto a = 10;    // int
auto b = 3.14;  // double
auto c = 'A';   // char

auto x;         // 에러! 초기값 없으면 추론 불가
```

Python처럼 편하지만, **한 번 추론되면 타입이 고정**된다.

```cpp
auto x = 10;
x = "hello";  // 에러! int로 고정됐기 때문
```

---

## 3. char — 범위와 메모리 절약

`char`은 1 byte, `int`는 4 bytes.  
범위 안의 값이면 `int` 대신 `char`로 메모리를 아낄 수 있다.

```cpp
char level = 5;  // 1 byte로 충분
int  level = 5;  // 4 bytes, 낭비

// char 범위: -128 ~ 127
```

---

## 4. 산술 변환 규칙 — 결과 타입은 더 큰 타입을 따라간다

두 타입이 다르면 **더 큰 타입으로 자동 변환 후 연산**된다.

```cpp
int + int       → int
int + double    → double
int + long long → long long
```

### ⚠️ 오버플로우 주의

연산이 **int 공간에서 먼저 일어나기 때문에** 결과를 long long에 저장해도 이미 늦다.

```cpp
long long result = 2000000000 * 2000000000;
// int * int → 오버플로우 → 엉뚱한 값이 long long에 저장됨
// warning: integer overflow, results in '-1651507200'
```

---

## 5. 접미사 — 오버플로우 방지

숫자 뒤에 접미사를 붙여 컴파일러에게 타입을 명시한다.

```cpp
long long result = 2000000000LL * 2000000000LL;  // long long끼리 연산 → 안전
```

| 접미사 | 타입 | 예시 |
|--------|------|------|
| `LL` | `long long` | `100LL` |
| `U` | `unsigned int` | `100U` |
| `f` | `float` | `3.14f` |
| 없음 | `double` | `3.14` |

> 한쪽만 붙여도 나머지가 자동으로 변환된다:  
> `2000000000LL * 2000000000` → 안전
