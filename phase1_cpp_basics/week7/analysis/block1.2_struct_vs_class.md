# `struct` vs `class` 정리

> 대상 코드: `dg3f_m_sdk_driver_debug.cpp` **[블록 1.2] `ReceivedGripperData` 타입** (SDK가 `DGDataTypes.h`에 정의)

`ReceivedGripperData`(SDK가 정의한 데이터 타입)를 보다가 "이거 struct야 class야?"를 정리한 문서.

---

## 1. `struct`란?

여러 개의 변수(데이터)를 **하나로 묶어서 새로운 타입을 만드는 것**.

```cpp
struct Point {
    int x;
    int y;
};

Point p;
p.x = 10;
p.y = 20;
```

`int x`, `int y`를 따로 들고 다니는 대신, `Point`라는 하나의 묶음(타입)으로 만들어 편하게 쓰는 것.

---

## 2. 진짜 차이는 "기본 접근 권한"뿐

```cpp
struct A {
    int x;     // 아무것도 안 썼는데, 자동으로 public
};

class B {
    int x;     // 아무것도 안 썼는데, 자동으로 private
};
```

| | 기본 접근 권한 (아무것도 안 썼을 때) |
|---|---|
| `struct` | `public` |
| `class` | `private` |

그 외엔 생성자, 멤버 함수, 상속 등 **모든 기능이 완전히 동일**하다.

### 명시하면 완전히 똑같이 동작

```cpp
struct A {
public:
    int x;
};

class B {
public:        // 명시하면 struct와 똑같이 동작
    int x;
};

A a; a.x = 10;  // OK
B b; b.x = 10;  // OK — public이라고 명시했으니 가능
```

즉 `class`에 `public:`을 붙이면 `struct`와 **완전히 동일**하게 동작한다.

---

## 3. 그럼 왜 둘을 구분해서 쓰나?

C++ 문법상으로는 차이가 거의 없지만, **관습(컨벤션)적으로 의도를 표현**하는 데 쓴다.

| | 보통 이렇게 씀 | 의도 |
|---|---|---|
| `struct` | 생성자/메서드 없이 단순 필드 묶음일 때 | "그냥 데이터를 담는 용도" — `public:`을 따로 안 써도 되니 편함 |
| `class` | 내부 데이터는 숨기고(`private`), 메서드로만 접근하게 만들 때 | "캡슐화가 중요한 객체" — 동작(메서드)이 중심 |

### 예시로 비교

```cpp
// struct: 데이터 묶음 (관습)
struct ReceivedGripperData {
    double position[12];
    double current[12];
    bool is_moving;
};

// class: 캡슐화 + 동작 중심 (관습)
class JointTrajectoryPublisher : public rclcpp::Node {
public:
    JointTrajectoryPublisher();
private:
    void timer_callback();          // 동작(메서드)
    rclcpp::TimerBase::SharedPtr timer_;  // 외부에서 직접 못 만지게 private
};
```

`ReceivedGripperData`는 "그리퍼에서 받은 데이터를 그냥 담아두는 용도"라서 `struct`로 정의했을 가능성이 높고, `JointTrajectoryPublisher`(week6에서 본 클래스)는 "노드의 동작을 캡슐화"하는 용도라서 `class`로 정의되어 있다 — 둘 다 문법적으로는 서로 바꿔 써도 동작하지만, **읽는 사람에게 "이게 단순 데이터냐, 캡슐화된 객체냐"를 전달하는 관습**으로 구분해서 쓴다.

---

## 한 줄 요약

> `struct`와 `class`는 기본 접근 권한(`public` vs `private`)만 다르고 기능은 동일하다.
> 구분해서 쓰는 이유는 문법적 필요가 아니라 **"이 타입이 단순 데이터 묶음인지, 캡슐화된 객체인지"를 코드 읽는 사람에게 전달하는 관습**이다.
