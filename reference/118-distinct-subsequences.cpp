#include "prelude.hpp"

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size();
        if (m > static_cast<int>(s.size())) return 0;
        vector<uint64_t> ways(m + 1, 0);
        ways[0] = 1;
        for (char c : s) {
            for (int j = m; j >= 1; --j) {
                if (t[j - 1] == c) {
                    ways[j] += ways[j - 1];
                }
            }
        }
        return static_cast<int>(ways[m]);
    }
};
