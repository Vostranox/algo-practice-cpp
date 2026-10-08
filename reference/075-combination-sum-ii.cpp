#include "prelude.hpp"

class Solution {
    vector<vector<int>> res;
    vector<int> cur;

    void dfs(const vector<int>& c, int start, int remaining) {
        if (remaining == 0) {
            res.push_back(cur);
            return;
        }
        for (int i = start; i < static_cast<int>(c.size()) && c[i] <= remaining; ++i) {
            if (i > start && c[i] == c[i - 1]) continue;
            cur.push_back(c[i]);
            dfs(c, i + 1, remaining - c[i]);
            cur.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, target);
        return res;
    }
};
