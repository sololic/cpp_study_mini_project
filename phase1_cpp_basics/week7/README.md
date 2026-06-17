# Week 7 — 실제 코드 분석: 그리퍼 SDK 드라이버

week6에 이어 실무 C++ 코드를 분석하는 주차.
DGSDK 기반 그리퍼 드라이버(`dg3f_m_sdk_driver.cpp`)를 블록 단위로 구조화하여 파악하는 것이 목표.

> 이전 내용 → [week6/README.md](../week6/README.md)

---

## 📊 학습 진행 현황

| 상태 | 내용 |
|:---:|------|
| 🔄 | SDK 드라이버 블록 구조 파악 (`dg3f_m_sdk_driver_debug.cpp`) |
| ⬜ | 사용된 C++ 문법 정리 (mutex, 콜백 스레드 안전성 등) |
| ⬜ | 직접 실습 |

> ⬜ 미완료 / 🔄 진행중 / ✅ 완료

---

## 📁 파일 구조

```
week7/
├── original/     ← 분석할 원본 코드 (수정 금지)
├── analysis/     ← 분석 메모 md
├── practice/     ← 블록 구조 주석을 추가한 디버그 버전 + 직접 실습한 코드
└── README.md
```
