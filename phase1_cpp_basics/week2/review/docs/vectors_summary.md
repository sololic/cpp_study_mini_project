# 동적 배열 (std::vector) 정리

---

## 📌 vector란?

크기가 자동으로 늘어나고 줄어드는 **동적 배열**이다.  
Python의 `list`와 거의 동일하다.

> Python `list`와 가장 유사한 C++ 자료구조다.  
> 단, C++은 타입을 명시해야 하고 (`vector<int>`, `vector<string>` 등)  
> `push_front`, `pop_front` 가 없다는 차이가 있다.

```cpp
#include <vector>

std::vector<int> v = {1, 2, 3};
```

---

## 📖 기본 operations

```cpp
std::vector<int> v = {1, 2, 3};

v.push_back(4);   // 뒤에 추가        (Python: append)
v.pop_back();     // 뒤에서 제거      (Python: pop)
v.size();         // 크기 반환        (Python: len)
v.empty();        // 비어있으면 true  (Python: not v)
v.front();        // 첫 번째 요소
v.back();         // 마지막 요소
v.clear();        // 전체 삭제
```

> `push_front`, `pop_front` 는 **없다**.  
> 앞에 추가/삭제가 필요하면 `std::deque` 사용.

### 인덱싱

```cpp
v[1]     // 인덱스 1 접근 (범위 초과 시 undefined behavior)
v.at(1)  // 인덱스 1 접근 (범위 초과 시 예외 발생 → 더 안전)
```

| 방식 | 범위 초과 시 | 권장 |
|:----:|:----------:|:----:|
| `v[n]` | 크래시 or 이상한 값 | 성능 중요할 때 |
| `v.at(n)` | 예외 발생, 정확한 에러 메시지 | 디버깅·안전 중요할 때 |

---

## 📖 반복문 3가지

```cpp
std::vector<int> v = {10, 20, 30, 40};

// (1) range-for — 가장 간단 (Python: for n in v)
for (int n : v) std::cout << n << " ";

// (2) 인덱스 (Python: for i in range(len(v)))
for (int i = 0; i < (int)v.size(); i++) std::cout << v[i] << " ";

// (3) range-for 참조 — 원본 값을 바꾸고 싶을 때
for (int& n : v) n *= 2;   // 참조(&) 없으면 원본 안 바뀜!
```

> `for (int n : v)` → 복사본, 원본 변경 안 됨  
> `for (int& n : v)` → 참조, 원본 변경 됨

---

## 📖 이터레이터 (iterator)

`begin()`, `end()`는 **이터레이터**를 반환한다.  
포인터처럼 벡터 안의 위치를 가리키는 것.

```cpp
v.begin()    // 첫 번째 요소를 가리킴
v.end()      // 마지막 요소 다음을 가리킴 (마지막 아님!)

*v.begin()       // 첫 번째 값
*(v.end() - 1)   // 마지막 값
```

### 범위는 [begin, end) — 끝은 포함 안 함

```
index:  0    1    2    3    4
value: [5,   2,   8,   1,   9]
        ↑                    ↑
     begin()               end()
                        (9 다음 위치)
```

Python 슬라이스와 동일한 방식: `v[0:5]` 에서 5는 미포함.

---

## 📖 정렬 & 검색

```cpp
#include <algorithm>

std::vector<int> v = {5, 2, 8, 1, 9};

// 정렬
std::sort(v.begin(), v.end());          // 전체 오름차순
std::sort(v.begin(), v.begin() + 3);    // 앞 3개만 정렬

// 검색
auto it = std::find(v.begin(), v.end(), 8);
if (it != v.end())   // 못 찾으면 end() 반환
    std::cout << "찾음, 인덱스: " << (it - v.begin());
```

---

## 📖 삽입 & 삭제

`insert`, `erase`는 **이터레이터**를 받는다. (`at()`이 아님!)

```cpp
v.insert(v.begin() + 2, 99);  // 인덱스 2에 99 삽입
v.erase(v.begin() + 2);       // 인덱스 2 삭제

// v.insert(v.at(2), 99);  // 에러! at()은 값 반환, 이터레이터 아님
```

---

## 📖 2D vector

```cpp
// 3x3 행렬, 0으로 초기화
std::vector<std::vector<int>> mat(3, std::vector<int>(3, 0));
// → { {0,0,0}, {0,0,0}, {0,0,0} }

mat[0][0] = 1;  // 0행 0열
mat[1][1] = 2;  // 1행 1열

// 이중 for문
for (auto& row : mat) {
    for (int val : row) std::cout << val << " ";
    std::cout << "\n";
}
```

Python 비교:
```python
mat = [[0]*3 for _ in range(3)]
for row in mat:
    for val in row:
        print(val, end=" ")
    print()
```

---

## 🔧 실전 활용

### 1. 센서 데이터 저장 (로보틱스)

```cpp
// 라이다 거리 데이터를 vector로 저장
std::vector<float> lidar_ranges;

// 새 데이터가 들어올 때마다 추가
lidar_ranges.push_back(1.23f);
lidar_ranges.push_back(0.95f);

// 가장 가까운 장애물 거리
float min_dist = *std::min_element(lidar_ranges.begin(), lidar_ranges.end());
```

### 2. ROS2 메시지 데이터

```cpp
// ROS2 라이다 메시지 구조 (실제 코드)
// sensor_msgs::msg::LaserScan 의 ranges 필드가 vector<float>
void scan_callback(const sensor_msgs::msg::LaserScan& msg) {
    std::vector<float> ranges = msg.ranges;  // 거리 데이터 배열
    for (float r : ranges) {
        if (r < 0.5f) {
            // 50cm 이내 장애물 감지
        }
    }
}
```

### 3. 경로 저장 (Path Planning)

```cpp
// 로봇 이동 경로를 좌표 벡터로 저장
struct Point { double x, y; };

std::vector<Point> path;
path.push_back({0.0, 0.0});
path.push_back({1.0, 0.5});
path.push_back({2.0, 1.0});

// 경로를 따라 순서대로 이동
for (const Point& p : path) {
    move_to(p.x, p.y);
}
```

### 4. 2D vector — 격자 맵 (Grid Map)

```cpp
// 로봇 주변 환경을 격자로 표현 (0: 빈공간, 1: 장애물)
int rows = 10, cols = 10;
std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));

grid[3][4] = 1;  // (3,4) 위치에 장애물
grid[5][6] = 1;  // (5,6) 위치에 장애물
```

---

## 📊 Python list vs C++ vector

| Python | C++ |
|--------|-----|
| `nums = [1, 2, 3]` | `vector<int> nums = {1, 2, 3};` |
| `nums.append(4)` | `nums.push_back(4);` |
| `len(nums)` | `nums.size()` |
| `nums.pop()` | `nums.pop_back();` |
| `nums[1]` | `nums[1]` or `nums.at(1)` |
| `for n in nums:` | `for (int n : nums)` |
| `nums.sort()` | `std::sort(nums.begin(), nums.end())` |
