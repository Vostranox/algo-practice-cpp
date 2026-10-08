#include "prelude.hpp"

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int goal = static_cast<int>(nums.size()) - 1;
        for (int i = goal - 1; i >= 0; --i) {
            if (i + nums[i] >= goal) {
                goal = i;
            }
        }
        return goal == 0;
    }
};
