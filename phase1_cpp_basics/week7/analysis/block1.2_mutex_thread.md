# 스레드 / mutex 정리 (Python 비교 중심)

> 대상 코드: `dg3f_m_sdk_driver_debug.cpp` **[블록 1.2] SDK 콜백 공유 데이터** (관련: [블록 1.3.1], [블록 2.5])

아래 코드가 무엇인지 정리한 문서.

```cpp
std::mutex g_data_mutex;
ReceivedGripperData g_latest_data = {};
```

---

## 1. 스레드(thread)란? — 새로 등장한 개념

프로그램 안에서 **동시에 실행되는 작업의 흐름**이다. 지금까지 본 코드(`dg3f_m_test.cpp` 등)는
"한 줄씩 순서대로 실행"되는 단일 스레드였지만, 이 드라이버는 **두 개의 스레드가 동시에 돈다.**

```
[dg3f_m_sdk_driver_debug.cpp 안에서 실제로 동시에 도는 두 흐름]

스레드 A: ROS 노드 (timer_callback)
  └─ 일정 주기로 g_latest_data를 읽어서 토픽으로 publish

스레드 B: DGSDK 내부 스레드 (on_received_data 콜백)
  └─ 그리퍼 하드웨어에서 새 데이터가 올 때마다 g_latest_data에 씀
```

이 둘은 "내가 호출해서" 실행되는 게 아니라, **각자 알아서 동시에 실행되는 별도의 실행 흐름**이라는 점이 지금까지 본 코드와 다르다.

### Python 비교

Python에서는 `threading.Thread`로 이런 동시 실행 흐름을 만든다.

```python
import threading

def ros_loop():       # 스레드 A 역할
    ...

def sdk_callback_loop():  # 스레드 B 역할
    ...

t1 = threading.Thread(target=ros_loop)
t2 = threading.Thread(target=sdk_callback_loop)
t1.start()
t2.start()
```

`dg3f_m_sdk_driver_debug.cpp`에서는 스레드를 직접 만들지는 않지만, **DGSDK 라이브러리가 내부적으로 별도 스레드를 만들어서 `on_received_data` 콜백을 그 스레드 위에서 호출**한다. 그래서 주석에 "DGSDK 콜백은 SDK 내부 스레드에서 호출되므로"라고 적혀있는 것.

---

## 2. 왜 문제가 되는가 — 데이터 레이스(race condition)

```cpp
ReceivedGripperData g_latest_data = {};  // 두 스레드가 공유
```

- 스레드 B: `g_latest_data = data;` (씀)
- 스레드 A: `data = g_latest_data;` (읽음)

이 둘이 **정확히 같은 시점에 일어나면**, A가 읽는 도중에 B가 값을 절반만 바꿔놓은 상태를 읽어버릴 수 있다 (특히 `ReceivedGripperData`처럼 필드가 여러 개인 구조체는 "한 번에 통째로" 바뀌는 게 보장되지 않음). 이런 현상을 **데이터 레이스(race condition)**라고 한다.

### Python에서도 같은 문제가 있을까?

Python은 **GIL(Global Interpreter Lock)** 때문에 한 순간엔 바이트코드 하나만 실행되지만, 그래도 race condition은 발생한다.

- 여러 줄에 걸쳐 객체의 필드 여러 개를 수정하는 도중에 다른 스레드가 끼어들 수 있음
- I/O 대기 중에는 다른 스레드로 전환되므로 더 취약함

그래서 Python도 공유 데이터를 다룰 땐 C++과 똑같이 **Lock이 필요**하다.

---

## 3. 해결책: `std::mutex` — 새로 등장한 개념

```cpp
std::mutex g_data_mutex;
```

`mutex`는 **"자물쇠"**다. 규칙은 단 하나:

> "이 데이터에 접근하려면 자물쇠를 먼저 잠가야 한다. 이미 잠겨있으면 풀릴 때까지 기다려라."

### Python 대응표

| C++ | Python | 의미 |
|---|---|---|
| `std::mutex` | `threading.Lock()` | 자물쇠 객체 생성 |
| `mutex.lock()` | `lock.acquire()` | 자물쇠 잠금 (이미 잠겨있으면 대기) |
| `mutex.unlock()` | `lock.release()` | 자물쇠 해제 |
| `std::lock_guard<std::mutex> lock(g_data_mutex);` | `with lock:` | 스코프(블록) 진입 시 자동 잠금, 빠져나갈 때 자동 해제 |

---

## 4. `std::lock_guard` — 새로 등장한 개념

실제 코드([블록 1.3.1])에서는 `mutex.lock()`을 직접 안 쓰고 `std::lock_guard`를 쓴다.

```cpp
void on_received_data(const ReceivedGripperData data) {
  std::lock_guard<std::mutex> lock(g_data_mutex);  // 여기서 자동 잠금
  g_latest_data = data;
}                                                   // 함수 끝나면서 자동 해제
```

`lock_guard`는 **"생성될 때 잠그고, 자기가 소멸될 때(스코프를 빠져나갈 때) 자동으로 해제해주는 객체"**다. 직접 `unlock()`을 호출할 필요가 없어서, 중간에 `return`이나 예외가 나도 자물쇠를 깜빡하고 안 푸는 실수를 막아준다.

### Python의 `with lock:`이 정확히 같은 역할

```python
def on_received_data(data):
    with g_data_mutex:      # 여기서 자동 acquire (= lock_guard 생성)
        global g_latest_data
        g_latest_data = data
    # with 블록을 빠져나가면서 자동 release (= lock_guard 소멸)
```

C++의 `lock_guard`와 Python의 `with lock:`은 둘 다 **"블록을 벗어나면 자동으로 자물쇠를 푼다"**는 동일한 패턴(RAII / context manager)을 구현한 것이다.

---

## 5. `timer_callback`(읽는 쪽)에서도 동일한 패턴

```cpp
// [블록 2.5] timer_callback 내부
{
  std::lock_guard<std::mutex> lock(g_data_mutex);
  data = g_latest_data;   // 복사
}
// 이후 data를 가지고 자물쇠 없이 자유롭게 사용 (publish 등)
```

**쓰는 쪽(`on_received_data`)과 읽는 쪽(`timer_callback`) 모두 같은 `g_data_mutex`를 잠그고 접근**해야, 둘 중 하나가 접근하는 동안 다른 하나는 반드시 대기하게 된다. 한쪽만 mutex를 쓰면 보호가 안 되므로 의미가 없다.

```python
# Python으로 옮기면
def on_received_data(data):           # 쓰는 쪽
    with g_data_mutex:
        global g_latest_data
        g_latest_data = data

def timer_callback():                 # 읽는 쪽
    with g_data_mutex:
        local_data = g_latest_data    # 복사해서 꺼냄
    # 이후 local_data로 publish 등 자유롭게 처리 (자물쇠 밖에서)
```

---

## 6. 전역 변수(`g_` 접두사) — 참고

```cpp
std::mutex g_data_mutex;
ReceivedGripperData g_latest_data = {};
```

`g_`는 "global(전역) 변수"라는 의미의 네이밍 컨벤션이다. 함수 밖에 선언되어 있어서, `on_received_data`와 `timer_callback` 양쪽에서 모두 접근 가능하다 — 이렇게 **여러 스레드/함수가 공유하는 상태**라서 mutex로 보호가 필요해진 것.

Python도 동일하게 모듈 최상단에 선언한 변수를 함수 안에서 `global` 키워드로 수정한다.

---

## 한 줄 요약

> SDK 콜백(스레드 B)과 ROS 타이머(스레드 A)가 `g_latest_data`라는 같은 데이터를 동시에 건드릴 수 있어서,
> `std::mutex`(자물쇠)로 보호한다. `std::lock_guard`는 "스코프를 빠져나가면 자동으로 자물쇠를 푸는" 도구이고,
> Python의 `threading.Lock()` + `with lock:`이 정확히 같은 역할을 한다.
