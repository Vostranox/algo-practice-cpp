#include "prelude.hpp"

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size();
        if (n + m != static_cast<int>(s3.size())) return false;
        vector<bool> ok(m + 1, false);
        ok[0] = true;
        for (int j = 1; j <= m; ++j) {
            ok[j] = ok[j - 1] && s2[j - 1] == s3[j - 1];
        }
        for (int i = 1; i <= n; ++i) {
            ok[0] = ok[0] && s1[i - 1] == s3[i - 1];
            for (int j = 1; j <= m; ++j) {
                ok[j] = (ok[j] && s1[i - 1] == s3[i + j - 1]) || (ok[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        return ok[m];
    }
};
