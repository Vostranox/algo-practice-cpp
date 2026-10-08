#include "prelude.hpp"

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size(), count = 0;
        for (int center = 0; center < 2 * n - 1; ++center) {
            int lo = center / 2, hi = (center + 1) / 2;
            while (lo >= 0 && hi < n && s[lo] == s[hi]) {
                ++count;
                --lo, ++hi;
            }
        }
        return count;
    }
};
