#include "prelude.hpp"

class Solution {
    vector<vector<int>> res;
    vector<int> cur;

    void dfs(int start, int n, int k) {
        if (static_cast<int>(cur.size()) == k) {
            res.push_back(cur);
            return;
        }
        for (int x = start; x <= n - (k - static_cast<int>(cur.size())) + 1; ++x) {
            cur.push_back(x);
            dfs(x + 1, n, k);
            cur.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        dfs(1, n, k);
        return res;
    }
};
