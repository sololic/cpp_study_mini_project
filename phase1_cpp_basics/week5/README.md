# Week 5 — 조건문·반복문

Part 03 (조건문·반복문) 기반 학습.  
개념 학습 → 문제 풀이 → 스터디 설명 순서로 진행.

> 이전 내용 → [week4/README.md](../week4/README.md)

---

## 📊 학습 진행 현황

| 상태 | 개념 | 세부 내용 |
|:---:|------|-----------|
| ⬜ | 조건문 & 반복문 | `switch`, `do-while`, `break`/`continue` |

### 문제 풀이

| 상태 | 주제 |
|:---:|------|
| ⬜ | 조건문·반복문 문제 |

> ⬜ 미완료 / ✅ 완료

---

## 📁 파일 구조

```
week5/
├── concepts/
│   ├── AI_basics/
│   │   ├── main.cpp                  ← 전체 실행 진입점
│   │   └── control_flow.cpp/h        ← 조건문·반복문 (switch, do-while, break/continue)
│   └── My_basics/      ← 직접 작성한 실습 코드
├── questions/          ← 문제 풀이
├── docs/               ← 개념 정리 md
└── README.md
```

---

## 📅 학습 내용

### 조건문 & 반복문 (Part 03)

| 주제 | 내용 | Python과 차이 |
|------|------|--------------|
| `switch` | 다중 분기, fall-through | Python에 없음 (`match` 제외), 문자열 불가 |
| `do-while` | 최소 1번 실행 보장 | Python에 없음 (`while True: ... if: break`로 흉내) |
| `break` / `continue` | 반복문 제어 | Python과 동일 |

---

## ⚙️ 빌드 & 실행

```bash
cd concepts/AI_basics
mkdir -p build

# 전체 실행
g++ -std=c++17 main.cpp control_flow.cpp -o build/week5 && ./build/week5

# 단독 실행
g++ -std=c++17 -DSTANDALONE control_flow.cpp -o build/cf && ./build/cf
```
