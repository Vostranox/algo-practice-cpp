#include "prelude.hpp"

class Solution {
    vector<vector<int>> res;
    vector<int> cur;

    void dfs(const vector<int>& nums, int i) {
        if (i == static_cast<int>(nums.size())) {
            res.push_back(cur);
            return;
        }
        cur.push_back(nums[i]);
        dfs(nums, i + 1);
        cur.pop_back();
        dfs(nums, i + 1);
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(nums, 0);
        return res;
    }
};
