#include "prelude.hpp"

class Solution {
    vector<vector<int>> res;
    vector<int> cur;

    void dfs(const vector<int>& c, int i, int remaining) {
        if (remaining == 0) {
            res.push_back(cur);
            return;
        }
        if (i == static_cast<int>(c.size()) || remaining < 0) return;
        cur.push_back(c[i]);
        dfs(c, i, remaining - c[i]);
        cur.pop_back();
        dfs(c, i + 1, remaining);
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(candidates, 0, target);
        return res;
    }
};
