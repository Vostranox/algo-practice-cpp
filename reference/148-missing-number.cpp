#include "prelude.hpp"

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = nums.size();
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            res ^= i ^ nums[i];
        }
        return res;
    }
};
