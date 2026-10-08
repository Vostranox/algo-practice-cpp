#include "prelude.hpp"

class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0, r = static_cast<int>(height.size()) - 1;
        int left_max = 0, right_max = 0, water = 0;
        while (l < r) {
            if (height[l] < height[r]) {
                left_max = max(left_max, height[l]);
                water += left_max - height[l++];
            } else {
                right_max = max(right_max, height[r]);
                water += right_max - height[r--];
            }
        }
        return water;
    }
};
