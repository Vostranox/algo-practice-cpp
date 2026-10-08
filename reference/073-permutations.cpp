#include "prelude.hpp"

class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used;

    void dfs(const vector<int>& nums) {
        if (cur.size() == nums.size()) {
            res.push_back(cur);
            return;
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            used[i] = true;
            cur.push_back(nums[i]);
            dfs(nums);
            cur.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        used.assign(nums.size(), false);
        dfs(nums);
        return res;
    }
};
