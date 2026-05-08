#include "vectors.h"
#include <iostream>
#include <vector>

// Python의 list와 거의 같다.
//  Python:  nums = [1, 2, 3];  nums.append(4)
//  C++:     vector<int> nums = {1,2,3};  nums.push_back(4);
void vectors() {
    std::vector<int> nums = {1, 2, 3};
    nums.push_back(4);

    std::cout << "[vector] ";
    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    std::cout << "크기: " << nums.size() << "\n\n";
}

#ifdef STANDALONE
int main() {
    vectors();
    return 0;
}
#endif