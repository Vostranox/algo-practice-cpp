#include "prelude.hpp"

class Solution {
    TreeNode* build(const vector<int>& nums, int lo, int hi) {
        if (lo > hi) return nullptr;
        int mid = lo + (hi - lo) / 2;
        return new TreeNode(nums[mid], build(nums, lo, mid - 1), build(nums, mid + 1, hi));
    }

public:
    TreeNode* sortedArrayToBST(vector<int>& nums) { return build(nums, 0, static_cast<int>(nums.size()) - 1); }
};
