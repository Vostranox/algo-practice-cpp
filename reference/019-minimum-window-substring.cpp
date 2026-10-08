#include "prelude.hpp"

class Solution {
public:
    string minWindow(string s, string t) {
        array<int, 128> need{};
        for (char c : t) {
            ++need[c];
        }
        int missing = t.size(), left = 0, best_left = 0, best_len = INT_MAX;
        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            if (need[s[right]]-- > 0) {
                --missing;
            }
            if (missing > 0) continue;
            while (need[s[left]] < 0) {
                ++need[s[left++]];
            }
            if (right - left + 1 < best_len) {
                best_left = left, best_len = right - left + 1;
            }
            ++need[s[left++]];
            ++missing;
        }
        return best_len == INT_MAX ? "" : s.substr(best_left, best_len);
    }
};
