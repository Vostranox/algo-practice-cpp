#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i + 2 < n && nums[i] <= 0; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int l = i + 1, r = n - 1;
            while (l < r) {
                int s = nums[i] + nums[l] + nums[r];
                if (s < 0) {
                    ++l;
                } else if (s > 0) {
                    --r;
                } else {
                    res.push_back({nums[i], nums[l], nums[r]});
                    ++l;
                    while (l < r && nums[l] == nums[l - 1]) {
                        ++l;
                    }
                    --r;
                }
            }
        }
        return res;
    }
};
