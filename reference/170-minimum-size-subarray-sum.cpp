#include "prelude.hpp"

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), best = n + 1, left = 0, sum = 0;
        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                best = min(best, right - left + 1);
                sum -= nums[left++];
            }
        }
        return best == n + 1 ? 0 : best;
    }
};
