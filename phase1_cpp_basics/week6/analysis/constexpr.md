# `constexpr` 정리

`dg3f_m_test.cpp`의 `constexpr double d2r(double deg) {...}`가 무엇인지 정리한 문서.
(예제 코드: [`practice/constexpr_example.cpp`](../practice/constexpr_example.cpp))

---

## 1. `constexpr`이란?

"**컴파일 타임(컴파일하는 시점)에 값을 계산할 수 있다**"는 걸 컴파일러에게 알려주는 키워드.

```cpp
constexpr double d2r(double deg) {
    return deg * 3.141592 / 180.0;
}

constexpr double r1 = d2r(80);  // 컴파일 시점에 미리 1.39626...으로 계산됨
```

---

## 2. 컴파일 타임 vs 런타임

| | 컴파일 타임 (compile-time) | 런타임 (runtime) |
|---|---|---|
| 시점 | 코드를 빌드(컴파일)하는 시점 | 빌드된 프로그램을 실행하는 시점 |
| 값을 아는 주체 | 컴파일러 | 프로그램(실행 중) |
| 예시 | `80`, `3.14` 같은 리터럴, `constexpr`/`const` 상수 | `cin`으로 받은 사용자 입력, 파일/센서에서 읽은 값 |

---

## 3. `const` vs `constexpr` (변수)

```cpp
int x;
std::cin >> x;        // x는 런타임에만 정해지는 값

const int a = x;       // ✅ OK — "a는 한 번 정해지면 안 바뀐다"는 의미일 뿐,
                        //    a의 "값"이 언제 정해지는지는 상관 안 함

constexpr int b = x;   // ❌ 에러 — "b는 반드시 컴파일 시점에 값이 확정돼야 한다"는
                        //    강제 조건인데, x는 런타임 값이라 불가능
```

| 키워드 | 의미 |
|---|---|
| `const` | "이 변수는 한 번 정해지면 안 바뀐다" (런타임에 정해져도 됨) |
| `constexpr` | "이 변수의 값은 **반드시 컴파일 시점에** 확정돼야 한다" (`const`보다 강한 보장) |

### 값이 지금 고정값(`10`)으로 보여도 안 되는 경우

```cpp
int x = 10;             // 그냥 보통 변수 (mutable) — "지금은 10"일 뿐, 바뀔 수 있음
constexpr int b = x;    // ❌ 에러
```

`x`가 지금 `10`을 담고 있어도, `int x`라는 **선언 자체가 "바뀔 수 있는 변수"**라는 뜻이라
컴파일러는 `x`를 컴파일 타임 상수로 인정하지 않는다.

```cpp
const int y = 10;
constexpr int b = y;    // ✅ OK — y는 "절대 안 바뀐다"고 선언했으므로

constexpr int z = 10;
constexpr int c = z;    // ✅ OK
```

---

## 4. `constexpr` 함수 — "강제"가 아니라 "허용"

`constexpr`을 **함수**에 붙이는 것과 **변수**에 붙이는 것은 의미가 다르다.

- `constexpr` **변수**: "이 값은 **반드시** 컴파일 타임에 알아야 함" (강제)
- `constexpr` **함수**: "이 함수는 (조건이 맞으면) 컴파일 타임에 계산해도 된다" (허용, 강제 아님)

```cpp
constexpr double d2r(double deg) {     // "deg를 받으면 이렇게 계산한다"는 공식/설계도
    return deg * 3.141592 / 180.0;     // deg가 뭔지 몰라도 정의 자체는 항상 유효
}
```

함수 **정의** 시점에는 `deg`가 컴파일 타임 값인지 런타임 값인지 알 필요가 없다.
실제로 어떤 식으로 계산되는지는 **호출하는 쪽**에서 결정된다.

---

## 5. 호출하는 쪽에 따라 달라지는 동작

```cpp
constexpr double r1 = d2r(80);          // ✅ 80은 컴파일 타임 값, r1도 constexpr
                                         //    → 컴파일 시점에 미리 계산됨

double user_deg;
std::cin >> user_deg;                   // user_deg는 런타임 값

double r2 = d2r(user_deg);              // ✅ OK — r2는 그냥 double (강제 없음)
                                         //    → d2r_normal(user_deg)처럼 런타임에 계산

constexpr double r3 = d2r(user_deg);    // ❌ 에러 — r3은 constexpr인데 user_deg가 런타임 값
```

| 호출 | 인자 | 결과를 받는 변수 | 동작 |
|---|---|---|---|
| `d2r(80)` | 컴파일 타임 값 | `constexpr double r1` | 컴파일 시점에 계산 |
| `d2r(user_deg)` | 런타임 값 | `double r2` (강제 없음) | 런타임에 계산 (일반 함수와 동일) |
| `d2r(user_deg)` | 런타임 값 | `constexpr double r3` | ❌ 에러 (모순) |

---

## 6. 비유로 정리

- `constexpr double d2r(double deg) {...}`
  → "deg를 주면 라디안으로 바꿔주는 계산기 설계도". 설계도는 deg 값과 무관하게 항상 그릴 수 있음.
- `constexpr double r1 = d2r(80);`
  → "이 계산기에 80을 넣고, **지금 당장(컴파일 시점)** 결과를 알려줘" → 가능
- `double r2 = d2r(user_deg);`
  → "이 계산기에 user_deg를 넣고, 결과를 알려줘 (언제 계산되든 상관없음)" → 가능 (런타임에 계산)
- `constexpr double r3 = d2r(user_deg);`
  → "이 계산기에 (아직 모르는) user_deg를 넣고, **지금 당장** 결과를 알려줘" → 불가능, 에러

---

## 7. 컴파일 타임 상수가 필요한 또 다른 예: 배열 크기

```cpp
constexpr int n = 5;
int arr[n];          // ✅ OK — 배열 크기는 컴파일 시점에 확정돼야 함

int ar = 4;
int arr2[ar];        // ❌ 에러 (VLA, variable length array)

const int m = 5;
int arr3[m];         // ❌ 에러 — const도 "런타임에 결정될 수 있는" 경우를 배제 못 해서
                     //    배열 크기로는 constexpr만 인정됨 (※ 컴파일러/표준에 따라 다를 수 있음)
```

---

## 8. `dg3f_m_test.cpp`에서의 실제 의미

```cpp
constexpr double d2r(double deg) {
    return deg * 3.141592 / 180.0;
}
...
angles_ = {
    {0, 0, d2r(0), d2r(0), ...},
    {0, 0, d2r(80), d2r(80), ...},
    ...
};
```

`d2r(80)`처럼 인자가 리터럴(고정값)이기 때문에, 컴파일러가 컴파일 시점에 "80도 = 1.3962634... 라디안"으로 미리 계산해서 박아넣는다. 실행 시점에는 이 계산을 다시 할 필요가 없다.

---

## 한 줄 요약

> `constexpr`은 변수에 붙으면 "반드시 컴파일 타임에 값이 확정돼야 한다"는 **강제**,
> 함수에 붙으면 "조건이 맞으면 컴파일 타임에 계산해도 된다"는 **허용**이다.
> `d2r`은 인자가 리터럴이면 컴파일 시점에 계산되고, 런타임 변수가 들어오면 그냥 평범한 함수처럼 동작한다.
