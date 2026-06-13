# `<chrono>` / `std::chrono_literals` / `using namespace` 정리

`dg3f_m_test.cpp`에 나오는 `2s`, `1s` 같은 표현이 무엇인지 정리한 문서.
(예제 코드: [`practice/chrono_literals_example.cpp`](../practice/chrono_literals_example.cpp))

---

## 1. `duration`이란?

`duration`은 **"시간의 길이(기간)"를 표현하는 클래스 타입**이다.
"몇 시인지(시각)"가 아니라 "얼마만큼의 시간인지(길이)"를 나타낸다.

```cpp
template<class Rep, class Period>
class duration {
    Rep value;   // 숫자값 (예: 2)
    // Period가 단위 (1초, 1분, 1밀리초 등)
};
```

| 타입 | 의미 |
|---|---|
| `std::chrono::seconds` | 초 단위 duration |
| `std::chrono::minutes` | 분 단위 duration |
| `std::chrono::milliseconds` | 밀리초 단위 duration |

### duration vs time_point

| | duration | time_point |
|---|---|---|
| 의미 | 시간의 **길이/간격** | 특정 **시점/시각** |
| 예시 | "2초", "5분" | "2026-06-13 14:30:00" |
| 비유 | "30분" (얼마나 걸리는지) | "오후 3시" (몇 시인지) |
| 관계 | `시각 + 기간 = 새로운 시각`, `시각 - 시각 = 기간` |

---

## 2. `#include <chrono>`

`<chrono>` 헤더는 `duration`, `time_point` 같은 타입들과,
`std::chrono_literals`라는 네임스페이스(아래 3번)를 정의하고 있다.
이 헤더가 있어야 위 타입들과 리터럴 접미사를 쓸 수 있다.

---

## 3. `std::chrono_literals` 네임스페이스

`<chrono>` 안에 정의된 네임스페이스로, **시간 리터럴 접미사(suffix)를 만들어주는 연산자 함수들**을 모아둔 곳.

```cpp
namespace std::chrono_literals {
    constexpr std::chrono::hours        operator""h  (unsigned long long);
    constexpr std::chrono::minutes      operator""min(unsigned long long);
    constexpr std::chrono::seconds      operator""s  (unsigned long long);
    constexpr std::chrono::milliseconds operator""ms (unsigned long long);
    constexpr std::chrono::microseconds operator""us (unsigned long long);
    constexpr std::chrono::nanoseconds  operator""ns (unsigned long long);
}
```

여기 들어있는 건 `seconds` 같은 **타입이 아니라**,
`2s` → `std::chrono::seconds(2)`로 변환해주는 **함수(`operator""s`)**다.

---

## 4. `operator` 키워드

C++에서 `a + b` 같은 연산자 사용은 사실 내부적으로 **함수 호출**이다.
`operator` 키워드는 이 연산자의 동작을 직접 함수로 정의(오버로딩)할 때 쓴다.

| 표현 | 의미 |
|---|---|
| `operator+`, `operator-`, `operator<<`, `operator==` 등 | **기존 연산자(기호)**가 이 타입에서 어떻게 동작할지 정의 |
| `operator""s`, `operator""ms` 등 (`operator` + `""`) | **새로운 리터럴 접미사**를 정의 |

즉 `operator` 뒤에 `""`가 붙으면 "접미사 문법 정의", 기존 기호(`+`, `<<`)가 붙으면 "그 연산자의 동작 정의"라는 차이가 있다.

---

## 5. 리터럴(literal)이란?

코드에 직접 박혀있는 고정된 값 자체.

```cpp
int x = 42;        // 42 ← 정수 리터럴
double pi = 3.14;  // 3.14 ← 실수 리터럴
"hello"            // 문자열 리터럴
```

여기에 **접미사**를 붙이는 문법도 원래 있었다 (`3.14f`, `100L`, `100u`).
C++11부터는 이 접미사를 사용자가 직접 정의할 수 있게 됐는데, 그게 `operator""`다.

```cpp
2s    // → operator""s(2) 호출 → std::chrono::seconds(2) 반환
500ms // → operator""ms(500) 호출 → std::chrono::milliseconds(500) 반환
```

---

## 6. `using namespace std::chrono_literals;`의 진짜 역할

`using namespace X;`의 역할은 항상 동일하다:
**"X 안의 이름들을 접두사 없이 쓸 수 있게 가져온다."** (파이썬의 `from math import *`와 동일)

다만 여기서 가져오는 건 일반 함수가 아니라 **리터럴 연산자(`operator""s` 등)**이고,
이 연산자는 **"unqualified(이름 그대로) 탐색"으로만 찾을 수 있다.**

→ 그래서 `using namespace std::chrono_literals;`가 없으면
`2s`라는 **짧은 리터럴 문법 자체가 컴파일 에러**가 된다.

### 대안: 필요한 것만 선택적으로 가져오기

```cpp
using std::chrono_literals::operator""s;  // s 접미사만 가져옴

auto sec = 2s;  // 가능
```

### 아예 안 가져오면?

`2s` 같은 짧은 문법은 못 쓰고, 원래 방식으로 직접 타입을 생성해야 한다.

```cpp
std::chrono::seconds sec(2);  // 짧은 리터럴 문법 대신 이렇게
```

---

## 7. `count()` — duration에서 숫자 꺼내기

`2s`, `500ms`, `1min` 같은 건 단순 숫자가 아니라 **클래스 객체**라서,
`std::cout`으로 바로 출력할 수 없다 (`operator<<`가 정의되어 있지 않음).

```cpp
std::cout << 2s;          // ❌ 컴파일 에러
std::cout << (2s).count(); // ✅ "2" 출력
```

`count()`는 duration 객체 안에 저장된 **"자기 단위 기준의 순수 숫자"**를 꺼내준다.

```cpp
(2s).count();    // 2     (초 단위 숫자)
(2000ms).count(); // 2000 (밀리초 단위 숫자)
(1min).count();   // 1     (분 단위 숫자)
```

→ 같은 "2초"라는 시간이라도, **어떤 타입(단위)으로 표현했느냐**에 따라 `count()` 결과가 다르다.

---

## 8. duration끼리의 연산

### 단위가 달라도 duration끼리는 연산 가능 (자동 변환)

```cpp
auto total = 1min + 30s;    // OK, 공통 단위(초)로 자동 변환
total.count();              // 90
```

### 일반 숫자와는 더하기/빼기 불가, 곱하기/나누기(배수)는 가능

```cpp
auto x = 2s + 5;    // ❌ 에러: int(5)와 duration은 더할 수 없음
auto y = 2s + 5s;   // ✅ OK
auto z = 2s * 3;    // ✅ OK → 6s (배수 연산은 허용)
```

### time_point(시각)와의 연산

```cpp
auto now   = std::chrono::system_clock::now(); // 현재 시각 (time_point)
auto later = now + 5s;                          // 5초 후 시각
auto diff  = later - now;                       // 다시 duration (5s)
```

- 시각 + 기간 = 새로운 시각
- 시각 - 시각 = 기간

---

## 9. `dg3f_m_test.cpp`에서의 실제 사용

```cpp
using namespace std::chrono_literals;  // 2s, 1s 리터럴 문법 활성화

timer_ = this->create_wall_timer(2s, ...);     // "2초"라는 주기(duration)로 타이머 생성
point.time_from_start = rclcpp::Duration(1s);  // "1초"라는 기간(duration)을 rclcpp::Duration으로 변환
```

`2s`, `1s`는 각각 `std::chrono::seconds(2)`, `std::chrono::seconds(1)`이고,
이 코드가 동작하는 이유는 `<chrono>` include + `using namespace std::chrono_literals;` 덕분이다.

---

## 10. `2s`를 변수에 안 담아도 바로 함수에 넘길 수 있는 이유

```cpp
timer_ = this->create_wall_timer(2s, ...);     // OK
point.time_from_start = rclcpp::Duration(1s);  // OK
std::cout << 2s;                               // ❌ 에러
```

`2s`는 이미 `std::chrono::seconds`라는 **완성된 객체**다. `2`, `"hello"` 같은 다른 리터럴처럼,
변수에 담지 않고 바로 함수 인자로 넘길 수 있다 — 이건 당연한 것이고 `auto x = 2s;`로
변수를 만들어야만 쓸 수 있는 게 아니다.

**관건은 "받는 쪽(함수 파라미터 / 생성자)이 duration 타입을 받도록 정의돼 있는가"** 이다.

| 사용처 | 받는 쪽 정의 | 결과 |
|---|---|---|
| `create_wall_timer(2s, ...)` | `template<typename DurationT> ... create_wall_timer(std::chrono::duration<...> period, ...)` — duration을 받는 파라미터 | ✅ OK |
| `rclcpp::Duration(1s)` | `rclcpp::Duration`에 `std::chrono::duration`을 받는 생성자가 있음 (duration → rclcpp::Duration 변환) | ✅ OK |
| `std::cout << 2s` | `operator<<(ostream&, std::chrono::seconds)` 같은 오버로드가 **없음** | ❌ 에러 |

즉:
- `create_wall_timer`: 파라미터 타입이 duration이라서 `2s`를 그대로 전달
- `rclcpp::Duration(1s)`: duration을 받는 생성자가 `1s`를 `rclcpp::Duration` 타입으로 변환
- `std::cout << 2s`: `ostream`에 `std::chrono::seconds`를 출력하는 `operator<<` 오버로드가 정의돼 있지 않아서 실패 → `.count()`로 숫자를 꺼내야 함 (7번 참고)

---

## 한 줄 요약

> `<chrono>`가 시간 관련 타입(`duration`, `time_point`)과 리터럴 연산자(`operator""s` 등)를 정의해두었고,
> `using namespace std::chrono_literals;`로 그 연산자들을 끌어와서 `2s`, `1s` 같은 짧은 문법을 쓸 수 있게 한 것.
> `2s`는 `std::chrono::seconds(2)`라는 **객체**이고, 그 안의 숫자를 꺼내려면 `.count()`를 쓴다.
