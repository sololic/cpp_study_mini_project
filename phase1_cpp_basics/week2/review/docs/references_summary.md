# 참조 (Reference) 정리

---

## 📌 참조란?

변수의 **별명(alias)** 이다. 같은 메모리를 가리키기 때문에 참조를 바꾸면 원본도 바뀐다.

```cpp
int a = 10;
int& ref = a;   // ref는 a의 별명

ref = 99;       // ref를 바꾸면 a도 바뀜
// a == 99
```

### Python 비교

Python에는 C++의 참조(`&`)처럼 명시적으로 별명을 선언하는 문법은 없다.  
단, mutable 객체(list, dict 등)를 함수에 넘기면 원본이 바뀌는 것과 유사한 효과가 있다.

```python
# Python — mutable 객체는 참조처럼 동작
def double_first(lst):
    lst[0] *= 2  # 원본 변경됨

nums = [10, 20, 30]
double_first(nums)
# nums == [20, 20, 30]

# 단, int 같은 immutable은 원본이 안 바뀜
def change(n):
    n = 99  # 원본 변경 안 됨

x = 10
change(x)
# x == 10 (그대로)
```

> C++ 참조는 int 같은 기본 타입도 원본을 바꿀 수 있다는 점이 Python과 다르다.

---

## ⚠️ 참조 선언 규칙

```cpp
int& ref = a;   // OK: 선언과 동시에 초기화
int& ref;       // 에러! 초기화 없이 선언 불가

int& ref1 = a;
int& ref2 = b;  // OK: 각각 따로 선언
// int& ref1 = a, & ref2 = b;  // 에러! 한 줄에 여러 참조 선언 불가
```

---

## 📖 참조 vs 값 복사

```cpp
int original = 5;

int copy = original;   // 값 복사 → 별개의 변수
int& ref  = original;  // 참조   → 같은 변수

copy = 100;  // original 그대로 (5)
ref  = 200;  // original도 변경 (200)
```

| 종류 | 원본 변경 | 독립 여부 |
|:----:|:--------:|:--------:|
| 값 복사 | ❌ | 독립적 |
| 참조 | ✅ | 같은 변수 |

---

## 📖 참조 vs 값 복사 — Python 비교

| 상황 | Python | C++ |
|------|--------|-----|
| int 전달 | 원본 변경 ❌ (immutable) | 값 복사 → 원본 변경 ❌ |
| int 참조 전달 | 불가 (문법 없음) | `int&` → 원본 변경 ✅ |
| list 전달 | 원본 변경 ✅ (mutable) | `vector` 값 복사 → 원본 변경 ❌ |
| list 참조 전달 | (기본 동작) | `vector&` → 원본 변경 ✅ |

---

## 📖 함수에서 참조 매개변수

```cpp
void double_value(int& n) {   // 참조로 받음 → 원본 변경
    n *= 2;
}

void no_change(int n) {        // 값으로 받음 → 복사본만 변경
    n *= 2;
}

int x = 10;
no_change(x);      // x = 10 (그대로)
double_value(x);   // x = 20 (변경됨)
```

---

## 📖 const 참조

읽기 전용 참조. 원본을 변경할 수 없다.

```cpp
int a = 42;
const int& cref = a;

// cref = 100;  // 에러! const 참조는 변경 불가
```

### const 참조 vs 일반 참조 — 리터럴 허용 여부

| 종류 | 변수 | 리터럴(임시값) |
|:----:|:----:|:--------------:|
| 일반 참조 (`int&`) | ✅ | ❌ |
| const 참조 (`const int&`) | ✅ | ✅ |

```cpp
int& ref      = 100;  // 에러! 일반 참조는 리터럴 불가
const int& ref = 100; // OK!  const 참조는 리터럴 가능
```

**왜 일반 참조는 리터럴을 못 받나?**
> 참조는 변수의 별명 → 수정 가능해야 함  
> 일반 참조는 "나 이거 바꿀 수도 있어" 선언 → 100은 고정값 → 컴파일러 거부 ❌

**왜 const 참조는 리터럴을 받을 수 있나?**
> const 참조는 "절대 안 바꿀게" 보장 → 컴파일러 허용 ✅  
> 컴파일러가 내부적으로 임시 변수를 만들어서 연결해줌

```cpp
// 컴파일러 내부 처리
int temp = 100;         // 임시 변수 생성 (자동)
const int& ref = temp;  // 임시 변수를 const 참조로 연결
```

---

## 🔧 실전 활용

### 1. 큰 데이터를 복사 없이 함수에 전달

```cpp
// ❌ 비효율: vector 전체를 복사해서 전달 (데이터가 클수록 느림)
void process(std::vector<int> data) { ... }

// ✅ 효율적: 참조로 전달 → 복사 없음
void process(const std::vector<int>& data) { ... }
```

> ROS2에서 센서 데이터(카메라 이미지, 라이다 포인트클라우드 등)는
> 크기가 매우 크기 때문에 `const 참조`로 전달하는 게 기본 패턴이다.

### 2. 함수에서 여러 값을 동시에 반환

```cpp
// Python은 tuple로 여러 값 반환 가능
// C++은 참조로 여러 값을 동시에 수정

void get_min_max(const std::vector<int>& v, int& min, int& max) {
    min = *std::min_element(v.begin(), v.end());
    max = *std::max_element(v.begin(), v.end());
}

int min_val, max_val;
get_min_max({3, 1, 7, 2, 9}, min_val, max_val);
// min_val = 1, max_val = 9
```

### 3. ROS2 콜백 함수

```cpp
// ROS2에서 토픽 메시지를 받을 때 const 참조로 받는 게 표준 패턴
void topic_callback(const std_msgs::msg::String& msg) {
    std::cout << msg.data << "\n";  // 복사 없이 읽기만
}
```

---

## 📊 참조 vs 포인터 비교

| | 참조 (`int&`) | 포인터 (`int*`) |
|--|:------------:|:--------------:|
| 초기화 | 선언과 동시에 필수 | 나중에 가능 |
| 재지정 | ❌ 불가 | ✅ 가능 |
| nullptr | ❌ 없음 | ✅ 가능 |
| 문법 | `ref = val` | `*ptr = val` |
| 용도 | 안전한 별명 | 주소 저장·조작 |
