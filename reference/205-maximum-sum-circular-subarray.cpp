#include "prelude.hpp"

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int total = 0, best = nums[0], worst = nums[0], hi = 0, lo = 0;
        for (int x : nums) {
            total += x;
            hi = max(hi + x, x), best = max(best, hi);
            lo = min(lo + x, x), worst = min(worst, lo);
        }
        return best < 0 ? best : max(best, total - worst);
    }
};
