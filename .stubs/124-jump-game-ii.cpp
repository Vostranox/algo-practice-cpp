/*
124. Jump Game II  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/jump-game-ii/

You start on index 0 of an array `nums` of non-negative integers. From index i
you may jump forward by any distance from 1 up to nums[i]. The input is
guaranteed to allow reaching the last index. Return the smallest number of
jumps needed to get there.

Example 1:
    Input:  nums = [4, 1, 1, 3, 1, 1, 1]
    Output: 2             (0 -> 3 -> 6; jumping as far as possible first,
                           to index 4, would need 3 jumps)

Example 2:
    Input:  nums = [1, 1, 1, 1]
    Output: 3

Example 3:
    Input:  nums = [0]
    Output: 0             (already on the last index)

Constraints:
    1 <= nums.length <= 10^4
    0 <= nums[i] <= 1000
    the last index is always reachable from index 0

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int jump(vector<int>& nums) {
        throw NotImplemented();
    }
};
