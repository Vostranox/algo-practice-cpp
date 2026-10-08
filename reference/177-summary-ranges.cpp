#include "prelude.hpp"

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        for (size_t i = 0, n = nums.size(); i < n;) {
            size_t j = i;
            while (j + 1 < n && static_cast<int64_t>(nums[j + 1]) == static_cast<int64_t>(nums[j]) + 1) {
                ++j;
            }
            res.push_back(i == j ? to_string(nums[i]) : to_string(nums[i]) + "->" + to_string(nums[j]));
            i = j + 1;
        }
        return res;
    }
};
