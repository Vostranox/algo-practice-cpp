#include "prelude.hpp"

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (abs(target) > total) return 0;
        vector<int> ways(2 * total + 1, 0);
        ways[total] = 1;
        for (int x : nums) {
            vector<int> next(2 * total + 1, 0);
            for (int s = 0; s <= 2 * total; ++s) {
                if (!ways[s]) continue;
                next[s + x] += ways[s];
                next[s - x] += ways[s];
            }
            ways = move(next);
        }
        return ways[target + total];
    }
};
