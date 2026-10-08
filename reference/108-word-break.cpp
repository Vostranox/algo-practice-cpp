#include "prelude.hpp"

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> ok(n + 1, false);
        ok[n] = true;
        for (int i = n - 1; i >= 0; --i) {
            for (const string& w : wordDict) {
                int j = i + static_cast<int>(w.size());
                if (j <= n && ok[j] && s.compare(i, w.size(), w) == 0) {
                    ok[i] = true;
                    break;
                }
            }
        }
        return ok[0];
    }
};
