#include "prelude.hpp"

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size(), bestLo = 0, bestLen = 1;
        for (int center = 0; center < 2 * n - 1; ++center) {
            int lo = center / 2, hi = (center + 1) / 2;
            while (lo >= 0 && hi < n && s[lo] == s[hi]) {
                --lo, ++hi;
            }
            if (hi - lo - 1 > bestLen) {
                bestLo = lo + 1, bestLen = hi - lo - 1;
            }
        }
        return s.substr(bestLo, bestLen);
    }
};
