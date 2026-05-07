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

- **Phase 1**: C++ 기초 문법부터 ROS2에 필요한 핵심 개념까지 2주간 집중 학습
- **Phase 2**: 프로그래머스 문제풀이로 C++ 실력을 다지고, 스터디에서 발표한 내용을 기록

---

## 📅 커리큘럼

### Phase 1 — C++ 기초 (2주)

> Python 경험을 기반으로 C++ 문법을 빠르게 습득하고, ROS2 코드를 읽고 쓸 수 있는 수준까지 도달

| 주차 | 주제 | 세부 내용 |
|:----:|------|-----------|
| Week 1 | C++ 기초 문법 | 자료형, 입출력, 참조(`&`), 포인터(`*`), 함수, `std::vector` |
| Week 2 | ROS2를 위한 C++ 핵심 | 클래스·상속, 스마트 포인터, 람다·콜백, 멀티스레드 기초 |

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
├── phase1_cpp_basics/          # C++ 기초 학습 예제
│   ├── week1/                  # 자료형, 포인터, 함수 등
│   └── week2/                  # 클래스, 스마트포인터, 콜백 등
│
├── phase2_problem_solving/     # 프로그래머스 문제풀이
│   ├── lv0/
│   │   ├── 문제이름.cpp        # 풀이 코드
│   │   └── 문제이름.md         # 문제 분석 노트
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