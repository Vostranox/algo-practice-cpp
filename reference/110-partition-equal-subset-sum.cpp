#include "prelude.hpp"

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % 2) return false;
        int target = total / 2;
        vector<char> can(target + 1, 0);
        can[0] = 1;
        for (int x : nums) {
            for (int s = target; s >= x; --s) {
                can[s] |= can[s - x];
            }
            if (can[target]) return true;
        }
        return false;
    }
};
