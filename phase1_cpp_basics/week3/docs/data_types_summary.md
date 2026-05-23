# 자료형 심화 (Data Types Advanced)

---

## 📌 왜 자료형 크기를 알아야 하나?

Python은 메모리를 자동으로 관리해주지만, C++은 개발자가 자료형을 직접 선택해야 한다.  
어떤 자료형이 메모리를 얼마나 쓰는지 알아야 **효율적인 코드**를 짤 수 있다.

> 한 줄 요약: **"메모리를 아끼고 싶거나, 크기가 정확히 맞아야 하는 상황에서 쓴다"**

---

## 📖 sizeof — 자료형 메모리 크기

```cpp
std::cout << sizeof(int)    << "\n";  // 4 bytes
std::cout << sizeof(double) << "\n";  // 8 bytes
std::cout << sizeof(char)   << "\n";  // 1 byte
```

| 자료형 | 크기 | 범위 |
|--------|:----:|------|
| `bool` | 1 byte | true / false |
| `char` | 1 byte | -128 ~ 127 |
| `int` | 4 bytes | 약 -21억 ~ 21억 |
| `long` | 4 or 8 bytes | 환경마다 다름 |
| `float` | 4 bytes | 소수점 7자리 |
| `double` | 8 bytes | 소수점 15자리 |

> Python은 int 크기 제한 없음 (자동 확장)  
> C++은 int = 4 bytes → 범위 초과 시 오버플로우 발생

---

## 📖 자료형별 핵심 특성

자료형 크기보다 **각 자료형의 특성과 언제 써야 하는지**가 더 중요하다.

| 자료형 | 핵심 | 언제 쓰나 |
|--------|------|-----------|
| `int` | 정수, 4 bytes | 일반적인 정수 연산 |
| `long` | 정수, 4 or 8 bytes | 환경마다 다름 → `long long` 권장 |
| `long long` | 정수, 8 bytes | int 범위 초과하는 큰 정수 |
| `double` | 실수, 8 bytes | 좌표, 속도, 각도 (정밀도 중요할 때) |
| `float` | 실수, 4 bytes | 메모리 절약 필요할 때 (double 대비) |
| `char` | 문자 1개 or 작은 정수, 1 byte | 문자 처리, -128~127 범위 정수 |
| `bool` | true/false | 조건 상태 저장 |
| `unsigned` | 음수 없는 정수 | 절대 음수가 될 수 없는 값 (밝기, 패킷 크기 등) |
| `auto` | 초기값으로 타입 자동 추론 | 타입이 길거나 복잡할 때 |

---

## 📖 auto — 타입 자동 추론

초기값을 보고 컴파일러가 타입을 자동으로 결정한다.  
반드시 **`= 값`과 함께** 써야 한다.

```cpp
auto a = 10;      // int
auto b = 3.14;    // double
auto c = true;    // bool
auto d = 'A';     // char
auto e = 3.14f;   // float

auto x;  // 에러! 초기값 없으면 타입 추론 불가
```

### Python과 차이

```python
x = 10
x = "hello"  # Python은 타입 자유롭게 변경 가능
```

```cpp
auto x = 10;   // int로 추론, 타입 고정
x = "hello";   // 에러! 한번 추론되면 변경 불가
```

> Python처럼 편하게 쓸 수 있지만, 한 번 추론되면 타입이 고정된다는 차이가 있다.

---

## 📖 long — 왜 쓰기 애매한가?

`long`은 플랫폼(OS/컴파일러)마다 크기가 달라진다.

```
Windows (MSVC)  : long = 4 bytes  (int와 동일)
Linux / macOS   : long = 8 bytes  (long long과 동일)
```

즉, 같은 코드를 Windows에서 빌드하면 4 bytes, Linux에서 빌드하면 8 bytes가 된다.  
**이식성이 없기 때문에 실무에서는 `long`을 거의 쓰지 않는다.**

### 대신 뭘 쓰나?

```cpp
// int 범위(21억)를 넘는 큰 정수가 필요할 때
long long big = 9223372036854775807LL;  // 약 922경, 8 bytes 보장

// 크기를 정확히 고정하고 싶을 때 (이식성 최우선)
#include <cstdint>
int32_t  a;  // 항상 4 bytes
int64_t  b;  // 항상 8 bytes
```

### 정리

| 상황 | 추천 자료형 |
|------|------------|
| 일반 정수 | `int` |
| 21억 초과하는 정수 | `long long` |
| 크기를 정확히 고정해야 할 때 | `int32_t`, `int64_t` |
| `long` | 사용 비추 (플랫폼마다 크기 다름) |

> Python은 정수 크기 제한이 없어서 이런 고민 자체가 없다.  
> C++에서는 큰 수가 필요하면 명시적으로 `long long`을 써야 한다.

---

## 📖 float vs double — 왜 정밀도 차이가 나나?

메모리 크기가 다르면 저장할 수 있는 **비트 수**가 달라진다.  
비트가 많을수록 더 세밀하게 표현할 수 있다.

```
float  = 4 bytes = 32 bits → 소수점 약 7자리까지
double = 8 bytes = 64 bits → 소수점 약 15자리까지
```

```cpp
float  f = 3.141592653589793f;
double d = 3.141592653589793;

// f 출력: 3.14159274  ← 7자리에서 오차 발생
// d 출력: 3.14159265  ← 15자리까지 정확
```

### 🔧 실전 활용
```
로봇 위치 계산 → double 권장 (오차 누적되면 경로 틀어짐)
라이다 거리값 → float 가능  (cm 단위면 7자리 정밀도로 충분)
```

> ROS2의 `LaserScan` 메시지에서 거리값이 `float`인 이유:  
> 거리값은 float 정밀도로 충분하고, 데이터가 수백 개씩 오기 때문에 메모리 절약이 중요하다.

---

## 📖 unsigned — 음수 없는 정수

일반 `int`는 음수/양수 둘 다 저장하지만, `unsigned`는 음수를 포기하는 대신 양수 범위가 2배 늘어난다.

```cpp
int           // -2,147,483,648 ~ 2,147,483,647 (약 -21억 ~ 21억)
unsigned int  //  0 ~ 4,294,967,295             (약 0 ~ 42억)
```

### 언제 쓰나?

> **"이 값은 절대 음수가 될 수 없다"는 의도를 명확히 표현할 때**

```cpp
unsigned int pixel_brightness = 255;  // 밝기는 0 이상만
unsigned int packet_size = 1024;      // 패킷 크기는 0 이상만
```

### 센서값과 인덱스는?

센서값이라도 음수가 가능한 건 unsigned를 쓰면 안 된다:

```
온도 센서    → -20°C 가능  → int or double  ← unsigned ❌
가속도 센서  → -9.8 가능   → double         ← unsigned ❌
라이다 거리  → 0 이상만    → float          ← unsigned 아님, float 사용
밝기·패킷   → 0 이상만    → unsigned ✅
```

인덱스의 경우 C++에서 `v.size()`가 `size_t`(unsigned)를 반환하는 이유는  
**메모리 주소는 음수가 없기 때문**이다. 단, 인덱스 계산에 음수가 나올 수 있는 상황이면 그냥 `int`를 쓰는 게 안전하다.

### ⚠️ 주의 — 언더플로우

```cpp
unsigned int u = 0;
u - 1;  // 언더플로우! → 4,294,967,295 (최댓값으로 돌아감)
```

0에서 1을 빼면 음수가 아니라 최댓값으로 돌아가는 버그가 생긴다.

---

## 📖 char — 왜 문자 처리에 쓰이나?

`string`은 문자 **여러 개**의 모음이고, `char`은 문자 **단 하나**다.

```cpp
char   c = 'A';        // 문자 1개 (작은따옴표)
string s = "Hello";    // 문자 여러 개 (큰따옴표)
```

`string`도 결국 `char`의 배열이다:
```cpp
string s = "Hello";
s[0]  // 'H' → char 하나
```

### char는 내부적으로 정수(ASCII)로 저장된다

```cpp
char c = 'A';
std::cout << c;        // A
std::cout << (int)c;   // 65  ← 'A'의 ASCII 코드
```

| 문자 | ASCII 값 |
|:----:|:--------:|
| `'A'` | 65 |
| `'a'` | 97 |
| `'0'` | 48 |

### "작은 정수"의 기준
`char`의 범위는 `-128 ~ 127`.  
이 범위 안의 값을 저장할 때 `int(4 bytes)` 대신 `char(1 byte)`를 쓰면 메모리를 아낄 수 있다.

```cpp
char level = 5;   // 1 byte로 충분
int  level = 5;   // 4 bytes, 낭비
```

---

---

## 📖 산술 변환 규칙 — 연산 결과의 타입은 어떻게 결정되나?

연산에 사용된 타입을 따라서 결과 타입이 결정된다.  
두 타입이 다르면 **더 큰 타입으로 자동 변환 후 연산**한다.

```cpp
int + int             → int
long long + long long → long long
int + double          → double   (int가 double로 자동 변환)
int + long long       → long long (int가 long long으로 자동 변환)
```

### ⚠️ 오버플로우 주의

```cpp
// 위험: int * int → int로 연산 → 결과가 int 범위 초과 → 오버플로우
long long result = 2000000000 * 2000000000;
// warning: integer overflow, results in '-1651507200'

// 안전: long long * long long → long long으로 연산
long long result = 2000000000LL * 2000000000LL;  // 4000000000000000000
```

한쪽만 `LL`을 붙여도 나머지가 자동으로 `long long`으로 변환되어 안전하다:
```cpp
long long result = 2000000000LL * 2000000000;  // 안전
```

### 접미사 종류

| 접미사 | 타입 | 예시 |
|--------|------|------|
| 없음 | `int` | `100` |
| `L` | `long` | `100L` |
| `LL` | `long long` | `100LL` |
| `U` | `unsigned int` | `100U` |
| `ULL` | `unsigned long long` | `100ULL` |
| `f` | `float` | `3.14f` |
| 없음 | `double` | `3.14` |

> 단순 대입은 접미사 없어도 자동 변환되지만,  
> **연산식 안에서 큰 수를 다룰 때**는 `LL` 등 접미사가 중요하다.

---

### 🔧 실전 활용

**1. 자료형 선택 기준**
```cpp
// 센서 값이 0~255 범위라면?
unsigned char sensor = 200;  // 1 byte로 충분, int(4 bytes) 낭비 불필요
```

**2. 로보틱스·임베디드**
로봇 컨트롤러는 메모리가 수 KB밖에 없는 경우가 많다.  
자료형 크기를 모르면 메모리 초과로 프로그램이 죽는다.

**3. ROS2 통신 프로토콜**
센서 데이터를 주고받을 때 데이터 크기가 정확히 맞아야 한다.  
`sizeof`로 크기를 확인하고 맞춰주는 작업이 필요하다.
