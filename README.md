# C++ for Robotics — 학습 기록

> Python 개발자가 로보틱스 실무를 목표로 C++을 학습하는 과정을 기록한 레포지토리

<br>

![C++](https://img.shields.io/badge/C++-17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Ubuntu](https://img.shields.io/badge/Ubuntu-24.04-E95420?style=flat-square&logo=ubuntu&logoColor=white)
![ROS2](https://img.shields.io/badge/ROS2-Jazzy-22314E?style=flat-square&logo=ros&logoColor=white)
![Programmers](https://img.shields.io/badge/Programmers-문제풀이-1e9d8b?style=flat-square)
![Status](https://img.shields.io/badge/Status-In%20Progress-f4c430?style=flat-square)

---

## 목차

1. [프로젝트 소개](#-프로젝트-소개)
2. [커리큘럼](#-커리큘럼)
3. [폴더 구조](#-폴더-구조)
4. [문제풀이 기록](#-문제풀이-기록)
5. [스터디 발표 기록](#-스터디-발표-기록)
6. [문제풀이 md 템플릿](#-문제풀이-md-템플릿)

---

## 📌 프로젝트 소개

Python을 주력으로 사용하던 개발자가 **로보틱스 실무**에 필요한 C++ 역량을 갖추기 위해 학습하는 과정을 정리한 레포지토리입니다.

- **Phase 1**: C++ 기초 문법부터 ROS2에 필요한 핵심 개념까지 체계적으로 학습
- **Phase 2**: 프로그래머스 문제풀이로 C++ 실력을 다지고, 스터디에서 발표한 내용을 기록

---

## 🔄 학습 방향 변경 (week3~)

> **왜 바꿨나?**

week1~2에서 자료형·참조·포인터·vector를 빠르게 학습했지만, 막상 스터디에서 설명하려고 하니 **겉으로만 알고 제대로 설명하지 못하는 상태**였다.

단순히 코드를 실행해보는 수준에서는 개념이 완전히 내 것이 되지 않는다는 걸 깨달았다.

> **어떻게 바꿨나?**

- 빠르게 진도 나가는 방식 → **완전히 이해하고 설명할 수 있을 때까지 다지는 방식**
- 학습 순서를 [C++ 입문에서 프로젝트까지](https://wikidocs.net/300272) 교재 기반으로 재구성
- 학습 방식: **개념 학습 → 문제 풀이 → 스터디에서 설명** 3단계로 고정

> **목표 기준**

각 개념마다 **"보지 않고 직접 설명할 수 있는 수준"** 이 될 때까지 반복한다.

---

## 📅 커리큘럼

### Phase 1 — C++ 기초

> Python 경험을 기반으로 C++ 문법을 체계적으로 익히고, ROS2 코드를 읽고 쓸 수 있는 수준까지 도달

| 주차 | Part | 주제 | 상태 |
|:----:|:---:|------|:---:|
| Week 1 | 05 | 자료형·입출력·참조·포인터·함수·vector 기초 | ✅ |
| Week 2 | 05 | week1 복습 (참조·포인터·동적배열) | ✅ |
| Week 3 | 02 | 자료형 심화 (sizeof·auto·타입변환·오버플로우·const) | ✅ |
| Week 4 | 02·03 | 연산자 심화·조건문·반복문 | 🔄 (연산자 ✅ / 조건문·반복문 ⬜) |
| Week 5 | 04·08·09·10 | 클래스·상속·다형성 | 🔄 |
| Week 6 | 07·11 | 함수 심화·모듈화 + 템플릿 | ⬜ |
| Week 7 | 14·15 | STL + 스마트 포인터 | ⬜ |
| Week 8 | 12·16 | 예외처리 + 스레드·동시성 | ⬜ |
| Week 9 | - | 통합 실습 | ⬜ |

📁 [phase1_cpp_basics/](./phase1_cpp_basics/)

---

### Phase 2 — 프로그래머스 문제풀이

> C++ 문법에 익숙해지기 위한 알고리즘 문제풀이 + 스터디 발표 기록

| 레벨 | 내용 |
|:----:|------|
| Lv.0 | C++ 기초 문법 적용 문제 |
| Lv.1 | 구현·완전탐색·문자열 처리 |
| Lv.2 | 자료구조·정렬·탐색 응용 |

📁 [phase2_problem_solving/](./phase2_problem_solving/)

---

## 📁 폴더 구조

```
cpp_study_mini_project/
│
├── phase1_cpp_basics/
│   ├── week1/                       # ✅ 자료형·참조·포인터·vector 기초
│   │   ├── concepts/
│   │   │   ├── AI_basics/           # 개념 예제 코드
│   │   │   └── My_basics/           # 직접 작성한 실습 코드
│   │   ├── questions/               # 문제 풀이
│   │   ├── week1_basics.cpp         # 리팩토링 전 단일 파일 (히스토리용)
│   │   └── README.md
│   ├── week2/                       # ✅ 참조·포인터·동적배열 복습
│   │   ├── review/
│   │   │   ├── AI_basics/           # 복습 예제 코드
│   │   │   ├── My_basics/           # 직접 작성한 복습 코드
│   │   │   └── docs/                # 개념 정리 md
│   │   ├── concepts/                # 새 개념 예제 (미진행)
│   │   ├── questions/               # 문제 풀이
│   │   └── README.md
│   ├── week3/                       # ✅ 자료형 심화
│   │   ├── concepts/
│   │   │   ├── AI_basics/           # 개념 예제 코드
│   │   │   └── My_basics/           # 직접 작성한 실습 코드
│   │   ├── questions/               # 문제 풀이
│   │   ├── docs/
│   │   │   ├── data_types_summary.md       # 자료형 심화 개념 정리
│   │   │   └── data_types_presentation.md  # 스터디 발표용 요약
│   │   └── README.md
│   └── week4/                       # 🔄 연산자 심화·조건문·반복문
│       ├── concepts/
│       │   ├── AI_basics/           # 개념 예제 코드
│       │   └── My_basics/           # 직접 작성한 실습 코드
│       ├── questions/               # 문제 풀이
│       ├── docs/                    # 개념 정리 md
│       └── README.md
│
├── phase2_problem_solving/          # 프로그래머스 문제풀이 (미시작)
│   ├── lv0/
│   ├── lv1/
│   └── lv2/
│
└── README.md
```

---

## 📝 문제풀이 기록

### Lv.0

| # | 문제 | 풀이 | 날짜 |
|:-:|------|:----:|:----:|
| 1 | - | - | - |

### Lv.1

| # | 문제 | 풀이 | 날짜 |
|:-:|------|:----:|:----:|
| 1 | - | - | - |

### Lv.2

| # | 문제 | 풀이 | 날짜 |
|:-:|------|:----:|:----:|
| 1 | - | - | - |

---

## 🎤 스터디 발표 기록

| 회차 | 날짜 | 발표 주제 | 자료 |
|:----:|------|-----------|:----:|
| 1회 | - | - | - |
| 2회 | - | - | - |
| 3회 | - | - | - |

---

## 📋 문제풀이 md 템플릿

> 각 문제 폴더 안의 `.md` 파일은 아래 형식으로 작성합니다.

```markdown
## 문제 이름

### 🔗 문제 링크
[프로그래머스 링크](https://programmers.co.kr/...)

---

### 💡 풀이 접근법

- 어떤 방식으로 접근했는지 서술
- 자료구조·알고리즘 선택 이유
- 시간·공간 복잡도 분석 (선택)

---

### 📚 배운 점

- C++ 문법 중 새로 알게 된 것
- Python과 다른 점
- 다음에 활용할 수 있는 패턴

---

### 💻 코드

\`\`\`cpp
#include <bits/stdc++.h>
using namespace std;

// 풀이 코드
\`\`\`
```

---

## 📚 참고 자료

- [learncpp.com](https://www.learncpp.com/) — C++ 문법 레퍼런스
- [프로그래머스](https://programmers.co.kr/) — 알고리즘 문제풀이
- [ROS2 Jazzy 공식 튜토리얼](https://docs.ros.org/en/jazzy/Tutorials.html)
- [The Cherno C++ YouTube](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb)