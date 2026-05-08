# Week 1 — C++ 기초 문법

Python 개발자 관점에서 C++ 핵심 개념을 정리한 파일 모음입니다.

---

## 파일 구조

```
week1/
├── concepts/
│   ├── AI_basics/        ← AI 생성 개념 예제
│   │   ├── main.cpp      ← 전체 실행 진입점
│   │   ├── data_types.cpp/h  ← 자료형
│   │   ├── references.cpp/h  ← 참조
│   │   ├── pointers.cpp/h    ← 포인터
│   │   └── vectors.cpp/h     ← 동적 배열 (std::vector)
│   └── My_basics/        ← 직접 작성한 추가 학습 코드
├── questions/            ← 개념 확인 문제 풀이
├── week1_basics.cpp      ← 리팩토링 전 단일 파일 (히스토리용)
└── README.md
```

---

## 빌드 & 실행 방법

### C++ 실행 흐름

Python은 `.py` 파일을 바로 실행하지만, C++은 반드시 **컴파일** 과정이 필요하다.

```
소스 파일 (.cpp)  →  [컴파일러: g++]  →  실행 파일 (바이너리)  →  실행
```

- **컴파일**: 사람이 읽는 코드를 컴퓨터가 실행할 수 있는 바이너리로 변환하는 과정
- **g++**: GNU C++ 컴파일러. `.cpp` 파일을 실행 파일로 만들어준다

---

### 빌드 명령어 분석

```bash
cd concepts/AI_basics
g++ -std=c++17 main.cpp data_types.cpp references.cpp pointers.cpp vectors.cpp -o week1
```

| 부분 | 의미 |
|------|------|
| `g++` | C++ 컴파일러 실행 |
| `-std=c++17` | C++17 표준 문법을 사용하겠다는 옵션 (버전 지정) |
| `main.cpp data_types.cpp ...` | 컴파일할 소스 파일들 (여러 개 나열) |
| `-o week1` | 출력(output) 파일 이름을 `week1`으로 지정 (`-o` = output) |

> `-std=c++17`을 생략하면 구버전 기준으로 컴파일되어 일부 문법이 동작하지 않을 수 있다.

---

### 실행 방법

```bash
./week1
```

- `./` : **현재 디렉토리**에 있는 파일을 실행하겠다는 의미
- Linux/Mac에서는 경로를 명시하지 않으면 시스템이 해당 파일을 찾지 못하기 때문에 `./`를 붙인다
- Windows에서는 `week1.exe`로 생성되며 `./week1` 또는 `week1` 으로 실행

---

### 전체 한번에 실행

```bash
# 0단계: AI_basics 폴더로 이동
cd concepts/AI_basics

# 1단계: 컴파일 (실행 파일 생성)
g++ -std=c++17 main.cpp data_types.cpp references.cpp pointers.cpp vectors.cpp -o week1

# 2단계: 실행
./week1
```

실행 결과:
```
[자료형]
int: 10
double: 3.14
...
[참조] x = 15
...
[포인터]
...
[vector] 1 2 3 4
...
```

---

### 주제별 단독 실행

`-DSTANDALONE` 플래그를 붙이면 해당 파일 하나만 단독으로 컴파일 & 실행할 수 있다.

```bash
# 자료형만
g++ -std=c++17 -DSTANDALONE data_types.cpp -o data_types
./data_types

# 참조만
g++ -std=c++17 -DSTANDALONE references.cpp -o references
./references

# 포인터만
g++ -std=c++17 -DSTANDALONE pointers.cpp -o pointers
./pointers

# 동적 배열만
g++ -std=c++17 -DSTANDALONE vectors.cpp -o vectors
./vectors
```

| 부분 | 의미 |
|------|------|
| `-DSTANDALONE` | `STANDALONE`이라는 이름을 **정의(Define)**하는 플래그 (`-D` = Define) |
| `data_types.cpp` | 이 파일 하나만 컴파일 |
| `-o data_types` | 출력 파일 이름을 `data_types`로 지정 |

---

## `#ifdef STANDALONE` 이란?

각 `.cpp` 파일 맨 아래에 이런 블록이 있다:

```cpp
#ifdef STANDALONE
int main() {
    pointers();
    return 0;
}
#endif
```

### 동작 원리

`#ifdef`는 **전처리기 지시문**이다. 컴파일 전에 조건을 확인해서 코드를 포함할지 말지 결정한다.

- `#ifdef STANDALONE` → `STANDALONE`이라는 이름이 **정의되어 있으면** 아래 코드를 포함
- `#endif` → 조건 블록 끝
- `-DSTANDALONE` → 컴파일 명령에서 `STANDALONE`을 정의하는 플래그

즉, 컴파일할 때 `-DSTANDALONE`을 붙이면 `#ifdef` 안의 `main()`이 활성화되고,
붙이지 않으면 해당 블록은 없는 것처럼 무시된다.

### 왜 이게 필요한가?

C++ 프로그램은 반드시 `main()` 함수가 **하나만** 존재해야 한다.

- 전체 실행 시: `main.cpp`의 `main()`이 사용됨 → 각 파일의 `#ifdef` 블록은 비활성화
- 단독 실행 시: 해당 `.cpp`에만 `-DSTANDALONE`을 붙여 컴파일 → 그 파일의 `main()`이 활성화

### 전처리기란?

컴파일은 사실 여러 단계로 나뉜다:

```
소스 코드  →  [전처리기]  →  [컴파일러]  →  [링커]  →  실행 파일
```

- **전처리기**: `#`으로 시작하는 지시문을 처리하는 단계. `#include`, `#ifdef`, `#define` 등
- `#ifdef`는 전처리 단계에서 조건에 맞지 않는 코드를 통째로 제거한다
- 컴파일러는 전처리기가 처리한 결과만 본다

---

## C++ 기본 문법 구조

Python과 다른 C++ 고유의 문법을 먼저 이해하면 코드 읽기가 훨씬 쉬워진다.

---

### 1. 세미콜론 `;`

C++은 모든 문장 끝에 `;`을 붙여야 한다. Python은 줄바꿈이 문장의 끝이지만, C++은 `;`이 끝을 알린다.

```cpp
// Python
x = 10

// C++
int x = 10;   // 세미콜론 필수
```

---

### 2. `#include` — 라이브러리 불러오기

Python의 `import`와 같은 역할이다. 기능을 사용하려면 해당 헤더를 포함해야 한다.

```cpp
#include <iostream>   // cout, cin 사용 (Python: import sys)
#include <string>     // string 타입 사용
#include <vector>     // vector 사용 (Python: list는 기본 내장)
```

| C++ | Python |
|-----|--------|
| `#include <iostream>` | `import sys` |
| `#include <string>` | (기본 내장) |
| `#include <vector>` | (기본 내장) |

> **`<iostream>`** : C++에서 표준 입출력 스트림을 제공하는 라이브러리.  
> 화면에 출력(`std::cout`)하거나 키보드로 입력(`std::cin`)받을 때 반드시 포함해야 한다.

---

### 3. `std::` — 네임스페이스

`std`는 C++ 표준 라이브러리의 이름공간(namespace)이다. `std::` 없이 쓰면 컴파일러가 어디서 온 건지 모른다.

```cpp
std::cout   // 표준 출력
std::string // 표준 문자열 타입
std::vector // 표준 동적 배열
```

Python으로 비유하면 `math.sqrt()`에서 `math.`과 같다. `sqrt()`만 쓰면 어느 모듈인지 모르는 것처럼, `cout`만 쓰면 어느 네임스페이스인지 모른다.

> `using namespace std;`를 파일 위에 선언하면 `std::` 생략 가능하지만, 이름 충돌 위험이 있어 학습용 외에는 권장하지 않는다.

---

### 4. `std::cout <<` — 출력

Python의 `print()`에 해당한다. `<<`는 **출력 연산자**로, 오른쪽 값을 화면에 출력한다.

```cpp
std::cout << "hello";         // hello 출력
std::cout << "int: " << a;    // "int: " 출력 후 a 값 출력 (체이닝 가능)
std::cout << a << "\n";       // a 출력 후 줄바꿈
```

`<<`를 여러 번 이어붙일 수 있다. Python의 `print("int:", a)` 와 같은 효과다.

| Python | C++ |
|--------|-----|
| `print("hello")` | `std::cout << "hello\n";` |
| `print("x =", x)` | `std::cout << "x = " << x << "\n";` |
| `print(a, b, c)` | `std::cout << a << b << c << "\n";` |

**`"\n"` vs `std::endl`**

둘 다 줄바꿈이지만 차이가 있다:
- `"\n"` : 줄바꿈 문자만 출력 (빠름)
- `std::endl` : 줄바꿈 + 출력 버퍼 강제 비우기 (느림)

일반적으로 `"\n"` 사용을 권장한다.

---

### 5. 함수 구조

Python과 구조가 다르다. 반환 타입을 앞에 명시해야 한다.

```
반환타입  함수이름 ( 매개변수타입 매개변수이름 ) {
    본문
}
```

```cpp
// 반환값 없음 → void
void say_hello() {
    std::cout << "hello\n";
}

// int를 반환
int add(int a, int b) {
    return a + b;
}
```

| Python | C++ |
|--------|-----|
| `def say_hello():` | `void say_hello() {` |
| `def add(a, b):` | `int add(int a, int b) {` |
| 들여쓰기로 블록 구분 | `{ }` 중괄호로 블록 구분 |

---

### 6. `main()` 함수

C++ 프로그램은 반드시 `main()` 함수에서 시작한다. `return 0`은 프로그램이 정상 종료됐다는 의미다.

```cpp
int main() {
    // 프로그램 시작점
    return 0;  // 0 = 정상 종료
}
```

Python의 `if __name__ == "__main__":` 블록과 역할이 유사하다.

---

## 각 파일 역할

### `data_types.cpp` — 자료형
C++은 변수를 선언할 때 타입을 반드시 명시해야 한다.

| C++ 타입 | Python 대응 | 예시 |
|----------|------------|------|
| `int` | `int` | `int x = 10;` |
| `double` | `float` | `double x = 3.14;` |
| `bool` | `bool` | `bool x = true;` |
| `char` | `str` (한 글자) | `char x = 'A';` |
| `std::string` | `str` | `string x = "hello";` |

---

### `references.cpp` — 참조 (`&`)
참조(`&`)는 변수의 **별명(alias)**이다. 참조를 통해 값을 바꾸면 원본도 바뀐다.

```cpp
void add_ten(int& n) {  // &: 참조로 받음
    n += 10;            // 원본 변수가 직접 변경됨
}

int x = 5;
add_ten(x);  // x = 15
```

Python에서 리스트처럼 mutable 객체를 함수에 넘기면 원본이 바뀌는 것과 유사하다.

---

### `pointers.cpp` — 포인터 (`*`, `&`)
포인터는 변수의 **메모리 주소**를 저장하는 변수다.

```cpp
int  val = 42;
int* ptr = &val;   // ptr에 val의 주소 저장

*ptr = 100;        // 역참조: ptr이 가리키는 곳의 값을 변경
// 결과: val == 100
```

| 기호 | 의미 |
|------|------|
| `&val` | val의 메모리 주소 |
| `int* ptr` | 주소를 저장하는 포인터 변수 선언 |
| `*ptr` | ptr이 가리키는 주소의 값 (역참조) |

---

### `vectors.cpp` — 동적 배열 (`std::vector`)
Python의 `list`와 거의 동일하다.

| Python | C++ |
|--------|-----|
| `nums = [1, 2, 3]` | `vector<int> nums = {1, 2, 3};` |
| `nums.append(4)` | `nums.push_back(4);` |
| `len(nums)` | `nums.size()` |
| `for n in nums:` | `for (int n : nums)` |

---

### `main.cpp` — 전체 실행
각 주제의 함수들을 순서대로 호출한다. 헤더 파일(`#include`)로 각 함수의 존재를 알린 뒤 실행한다.

```cpp
#include "data_types.h"
#include "references.h"
#include "pointers.h"
#include "vectors.h"

int main() {
    data_types();
    references();
    pointers();
    vectors();
}
```

---

## `.cpp` 와 `.h` 를 나누는 이유

Python은 파일 하나에 함수를 정의하고 바로 `import`해서 쓰면 된다.  
C++은 **선언(declaration)** 과 **정의(definition)** 를 분리하는 관습이 있다.

| 파일 | 역할 | 포함 내용 |
|------|------|-----------|
| `.h` (헤더) | 선언 | 함수 이름, 매개변수, 반환 타입만 명시 |
| `.cpp` (소스) | 정의 | 실제 함수 구현 코드 |

---

### 왜 나누는가?

**1. 컴파일 단위 분리**

C++은 파일 단위로 컴파일된다. `.cpp` 파일 하나가 하나의 컴파일 단위다.  
`main.cpp`가 `pointers.cpp`의 함수를 쓰려면, 그 함수가 **존재한다는 사실(선언)** 을 먼저 알아야 한다.  
`.h` 파일이 그 역할을 한다.

```
main.cpp  →  #include "pointers.h"  →  "pointers() 함수가 있구나" (선언 확인)
                                    →  링커가 pointers.cpp의 구현과 연결
```

**2. 재사용성**

`.h`만 `#include`하면 어느 파일에서든 해당 함수를 쓸 수 있다.  
구현(`cpp`)을 몰라도 **인터페이스(h)** 만 알면 사용 가능하다.  
Python의 `import`와 비슷하지만, 선언과 구현이 명시적으로 분리된 구조다.

**3. 컴파일 속도**

파일이 많아지면 변경된 `.cpp`만 다시 컴파일하면 된다.  
헤더만 바뀌지 않았다면 다른 파일은 재컴파일 불필요 → 빌드 속도 향상.

---

### 어떻게 나누는가?

**`.h` 에 들어가는 것 — 선언만**

```cpp
// pointers.h
#pragma once          // 이 헤더가 중복 포함되지 않도록 방지

void pointers();      // 함수 선언 (이름 + 매개변수 + 반환타입만)
```

**`.cpp` 에 들어가는 것 — 구현**

```cpp
// pointers.cpp
#include "pointers.h"   // 자신의 헤더 포함
#include <iostream>

void pointers() {        // 실제 구현
    int val = 42;
    int* ptr = &val;
    std::cout << "[포인터] val: " << val << "\n";
    // ...
}
```

**다른 파일에서 사용할 때**

```cpp
// main.cpp
#include "pointers.h"   // 선언만 가져옴

int main() {
    pointers();         // 링커가 pointers.cpp의 구현과 연결해줌
    return 0;
}
```

---

### `#pragma once` 란?

헤더 파일 맨 위에 쓰는 전처리기 지시문이다.

```cpp
#pragma once
```

같은 헤더가 여러 파일에서 중복 `#include` 되면 선언이 중복돼 컴파일 오류가 난다.  
`#pragma once`는 **한 번만 포함되도록** 자동으로 막아준다.

| 방식 | 코드 |
|------|------|
| `#pragma once` (현대적, 권장) | `#pragma once` |
| Include Guard (전통적) | `#ifndef POINTERS_H` / `#define POINTERS_H` / `#endif` |

---

### Python vs C++ 비교

| | Python | C++ |
|--|--------|-----|
| 선언/정의 분리 | 없음 (하나의 파일) | `.h` (선언) + `.cpp` (정의) |
| 가져오기 | `import pointers` | `#include "pointers.h"` |
| 실행 연결 | 인터프리터가 자동 처리 | 링커가 `.cpp` 구현과 연결 |

