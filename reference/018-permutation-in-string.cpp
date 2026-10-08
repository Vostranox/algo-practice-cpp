#include "prelude.hpp"

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        if (m > n) return false;
        array<int, 26> need{}, have{};
        for (int i = 0; i < m; ++i) {
            ++need[s1[i] - 'a'];
            ++have[s2[i] - 'a'];
        }
        int matches = 0;
        for (int i = 0; i < 26; ++i) {
            matches += need[i] == have[i];
        }
        auto update = [&](int i, int delta) {
            if (have[i] == need[i]) {
                --matches;
            }
            have[i] += delta;
            if (have[i] == need[i]) {
                ++matches;
            }
        };
        for (int r = m; r < n; ++r) {
            if (matches == 26) return true;
            update(s2[r] - 'a', +1);
            update(s2[r - m] - 'a', -1);
        }
        return matches == 26;
    }
};
