# `const` 매개변수 정리

> 대상 코드: `dg3f_m_sdk_driver_debug.cpp` **[블록 1.3.1] `on_received_data`**

```cpp
void on_received_data(const ReceivedGripperData data) {
  std::lock_guard<std::mutex> lock(g_data_mutex);
  g_latest_data = data;
}
```

---

## 핵심만 정리

| 구성 | 의미 |
|---|---|
| `ReceivedGripperData` | 매개변수의 **타입** |
| `data` | 매개변수 **이름** — 호출 시 전달된 값의 **복사본** (참조 `&`/포인터 `*` 없음) |
| `const` | 함수 안에서 `data`를 **수정하지 못하게** 막음 (읽기 전용) |

```cpp
data.position[0] = 5;  // ❌ 에러 (const라서 수정 불가)
g_latest_data = data;  // ✅ OK (읽기만 함)
```

## 왜 복사본인데도 `const`를 붙이나

복사본이라 원본엔 영향 없지만, "이 함수는 받은 데이터를 읽기만 한다"는 의도를 표시하고 실수로 수정하는 걸 컴파일러가 막아준다.

---

## 한 줄 요약

> `const ReceivedGripperData data`는 "ReceivedGripperData 타입의 값을 복사받아서, 함수 안에서는 그 복사본조차 수정하지 않겠다"는 선언이다.
