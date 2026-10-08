/*
73. Permutations  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/permutations/

Given an array `nums` of distinct integers, return every possible ordering
(permutation) of its elements, each exactly once. The permutations may be
returned in any order (but each one is, of course, an ordered list).

Example 1:
    Input:  nums = [5, 8]
    Output: [[5, 8], [8, 5]]

Example 2:
    Input:  nums = [0, -2, 3]
    Output: [[0, -2, 3], [0, 3, -2], [-2, 0, 3], [-2, 3, 0], [3, 0, -2], [3, -2, 0]]

Example 3:
    Input:  nums = [4]
    Output: [[4]]

Constraints:
    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    all values in nums are distinct

Target: O(n * n!) backtracking -- choose each unused element for the next
position, recurse, then undo the choice.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        throw NotImplemented();
    }
};
