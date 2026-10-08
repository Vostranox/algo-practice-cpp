#include "prelude.hpp"

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> values(nums.begin(), nums.end());
        int best = 0;
        for (int x : values) {
            if (values.count(x - 1)) continue;
            int len = 1;
            while (values.count(x + len)) {
                ++len;
            }
            best = max(best, len);
        }
        return best;
    }
};
