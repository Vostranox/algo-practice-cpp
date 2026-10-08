#include "prelude.hpp"

class Solution {
    static int first_at_least(const vector<int>& nums, int64_t x) {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < x) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return lo;
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = first_at_least(nums, target);
        if (first == static_cast<int>(nums.size()) || nums[first] != target) return {-1, -1};
        return {first, first_at_least(nums, static_cast<int64_t>(target) + 1) - 1};
    }
};
