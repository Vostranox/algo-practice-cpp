#include "prelude.hpp"

class Solution {
public:
    int characterReplacement(string s, int k) {
        int count[26] = {};
        int left = 0, max_freq = 0, best = 0;
        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            max_freq = max(max_freq, ++count[s[right] - 'A']);
            while (right - left + 1 - max_freq > k) {
                --count[s[left++] - 'A'];
            }
            best = max(best, right - left + 1);
        }
        return best;
    }
};
