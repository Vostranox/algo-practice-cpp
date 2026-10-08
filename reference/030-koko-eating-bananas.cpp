#include "prelude.hpp"

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1, hi = *max_element(piles.begin(), piles.end());
        while (lo < hi) {
            int k = lo + (hi - lo) / 2;
            int64_t need = 0;
            for (int p : piles) {
                need += (p + static_cast<int64_t>(k) - 1) / k;
            }
            if (need <= h) {
                hi = k;
            } else {
                lo = k + 1;
            }
        }
        return lo;
    }
};
