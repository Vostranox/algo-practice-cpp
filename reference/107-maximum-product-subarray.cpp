#include "prelude.hpp"

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int best = nums[0], hi = nums[0], lo = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            int x = nums[i];
            int a = x * hi, b = x * lo;
            hi = max({x, a, b});
            lo = min({x, a, b});
            best = max(best, hi);
        }
        return best;
    }
};
