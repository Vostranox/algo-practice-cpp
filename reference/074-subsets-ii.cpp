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
        while (i + 1 < static_cast<int>(nums.size()) && nums[i + 1] == nums[i]) {
            ++i;
        }
        dfs(nums, i + 1);
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return res;
    }
};
