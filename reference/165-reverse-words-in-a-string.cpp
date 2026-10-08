#include "prelude.hpp"

class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        size_t out = 0, n = s.size();
        for (size_t i = 0; i < n;) {
            if (s[i] == ' ') {
                ++i;
                continue;
            }
            if (out > 0) {
                s[out++] = ' ';
            }
            size_t start = out;
            while (i < n && s[i] != ' ') {
                s[out++] = s[i++];
            }
            reverse(s.begin() + start, s.begin() + out);
        }
        s.resize(out);
        return s;
    }
};
