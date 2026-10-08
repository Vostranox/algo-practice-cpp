#include "prelude.hpp"

class Solution {
public:
    int mySqrt(int x) {
        int64_t lo = 0, hi = min<int64_t>(x, 46340);
        while (lo < hi) {
            int64_t mid = (lo + hi + 1) / 2;
            if (mid * mid <= x) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return static_cast<int>(lo);
    }
};
