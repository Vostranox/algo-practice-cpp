/*
71. Subsets  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/subsets/

Given an array `nums` of distinct integers, return all of its subsets (the power
set): every selection of zero or more of its elements, including the empty
subset and nums itself. Each subset must appear exactly once. Return the subsets
in any order; the numbers inside a subset may also be in any order.

Example 1:
    Input:  nums = [4, 7]
    Output: [[], [4], [7], [4, 7]]

Example 2:
    Input:  nums = [-1, 0, 5]
    Output: [[], [-1], [0], [5], [-1, 0], [-1, 5], [0, 5], [-1, 0, 5]]

Example 3:
    Input:  nums = [9]
    Output: [[], [9]]

Constraints:
    1 <= nums.length <= 10
    -10 <= nums[i] <= 10
    all values in nums are distinct

Target: O(n * 2^n) -- for each element, branch on "take it" / "skip it".
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        throw NotImplemented();
    }
};
