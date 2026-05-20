# Week 3 — 기본 문법 심화 & 제어문

Part 02 (기본 문법) + Part 03 (조건문·반복문) 기반 학습.  
개념 학습 → 문제 풀이 → 스터디 설명 순서로 진행.

> 이전 내용 → [week2/README.md](../week2/README.md)

---

## 📊 학습 진행 현황

| 상태 | 개념 | 세부 내용 |
|:---:|------|-----------|
| ⬜ | 자료형 심화 | `sizeof`, `auto`, 타입변환, 오버플로우, `const`/`constexpr` |
| ⬜ | 연산자 심화 | 정수나눗셈, `++`/`--`, 삼항연산자, 비트연산자 |
| ⬜ | 조건문 & 반복문 | `switch`, `do-while`, `break`/`continue` |

### 문제 풀이

| 상태 | 주제 |
|:---:|------|
| ⬜ | 자료형 심화 문제 |
| ⬜ | 연산자 심화 문제 |
| ⬜ | 조건문·반복문 문제 |

> ⬜ 미완료 / ✅ 완료

---

## 📁 파일 구조

```
week3/
├── concepts/
│   ├── AI_basics/
│   │   ├── main.cpp                  ← 전체 실행 진입점
│   │   ├── data_types_advanced.cpp/h ← 자료형 심화 (sizeof, auto, 타입변환, 오버플로우, const)
│   │   ├── operators.cpp/h           ← 연산자 심화 (정수나눗셈, ++/--, 삼항, 비트)
│   │   └── control_flow.cpp/h        ← 조건문·반복문 (switch, do-while, break/continue)
│   └── My_basics/      ← 직접 작성한 실습 코드
├── questions/          ← 문제 풀이
├── docs/               ← 개념 정리 md
└── README.md
```

---

## 📅 학습 내용

### 1. 자료형 심화 (Part 02)

| 주제 | 내용 | Python과 차이 |
|------|------|--------------|
| `sizeof` | 자료형이 메모리를 얼마나 쓰는지 | Python은 자동 관리 |
| `auto` | 타입 자동 추론 | Python 변수 선언과 유사 |
| 타입 변환 | 암시적·명시적 변환, 데이터 손실 | Python은 자동 변환 |
| 오버플로우 | int 범위 초과 시 발생 | Python은 자동 확장 |
| `const` / `constexpr` | 변경 불가 변수 | Python `final` 없음 |

### 2. 연산자 심화 (Part 02)

| 주제 | 내용 | Python과 차이 |
|------|------|--------------|
| 정수 나눗셈 | `5/2 = 2` | Python `5/2 = 2.5` |
| `++` / `--` | 전위·후위 증감 | Python에 없음 |
| 삼항 연산자 | `조건 ? 참 : 거짓` | Python `참 if 조건 else 거짓` |
| 비트 연산자 | `&`, `\|`, `^`, `<<`, `>>` | Python과 동일 |

### 3. 조건문 & 반복문 (Part 03)

| 주제 | 내용 | Python과 차이 |
|------|------|--------------|
| `switch` | 다중 분기 | Python에 없음 (`match` 제외) |
| `do-while` | 최소 1번 실행 보장 | Python에 없음 |
| `break` / `continue` | 반복문 제어 | Python과 동일 |

---

## ⚙️ 빌드 & 실행

```bash
cd concepts/AI_basics

# 전체 실행
g++ -std=c++17 main.cpp data_types_advanced.cpp operators.cpp control_flow.cpp -o week3 && ./week3

# 주제별 단독 실행
g++ -std=c++17 -DSTANDALONE data_types_advanced.cpp -o dt && ./dt
g++ -std=c++17 -DSTANDALONE operators.cpp -o op && ./op
g++ -std=c++17 -DSTANDALONE control_flow.cpp -o cf && ./cf
```
