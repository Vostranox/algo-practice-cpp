/*
206. Search Insert Position  ·  Easy  ·  Binary Search
Source: https://leetcode.com/problems/search-insert-position/

`nums` holds distinct integers sorted in increasing order. If `target` occurs in
nums, return its index. Otherwise return the index at which target would have
to be inserted to keep nums sorted (this can be nums.length, past the end).

Your algorithm must run in O(log n) time. (One test calls searchInsert() about
a million times on a 10^4-element vector, so a linear scan times out.)

Example 1:
    Input:  nums = [-6, -1, 3, 8, 12], target = 8
    Output: 3

Example 2:
    Input:  nums = [-6, -1, 3, 8, 12], target = 4
    Output: 3             (4 belongs between 3 and 8)

Example 3:
    Input:  nums = [-6, -1, 3, 8, 12], target = 20
    Output: 5             (after the last element)

Constraints:
    1 <= nums.length <= 10^4
    -10^4 <= nums[i], target <= 10^4
    all values in nums are distinct, and nums is sorted in increasing order
*/
#include "prelude.hpp"

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        throw NotImplemented();
    }
};
