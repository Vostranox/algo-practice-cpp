#include "prelude.hpp"

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(256, -1);
        int left = 0, best = 0;
        for (int r = 0; r < static_cast<int>(s.size()); ++r) {
            unsigned char c = s[r];
            if (last[c] >= left) {
                left = last[c] + 1;
            }
            last[c] = r;
            best = max(best, r - left + 1);
        }
        return best;
    }
};
