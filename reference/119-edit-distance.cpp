#include "prelude.hpp"

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> prev(m + 1), cur(m + 1);
        iota(prev.begin(), prev.end(), 0);
        for (int i = 1; i <= n; ++i) {
            cur[0] = i;
            for (int j = 1; j <= m; ++j) {
                cur[j] = word1[i - 1] == word2[j - 1] ? prev[j - 1] : 1 + min({prev[j], cur[j - 1], prev[j - 1]});
            }
            swap(prev, cur);
        }
        return prev[m];
    }
};
