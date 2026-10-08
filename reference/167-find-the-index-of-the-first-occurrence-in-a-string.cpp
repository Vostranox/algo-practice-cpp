#include "prelude.hpp"

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int> fail(m, 0);
        for (int i = 1, k = 0; i < m; ++i) {
            while (k > 0 && needle[i] != needle[k]) {
                k = fail[k - 1];
            }
            if (needle[i] == needle[k]) {
                ++k;
            }
            fail[i] = k;
        }
        for (int i = 0, k = 0; i < n; ++i) {
            while (k > 0 && haystack[i] != needle[k]) {
                k = fail[k - 1];
            }
            if (haystack[i] == needle[k]) {
                ++k;
            }
            if (k == m) return i - m + 1;
        }
        return -1;
    }
};
