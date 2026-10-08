/*
122. Maximum Subarray  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/maximum-subarray/

You get an integer array `nums`. Choose a contiguous, non-empty stretch of it
(a subarray) whose elements add up to as much as possible, and return that
largest possible sum.

Example 1:
    Input:  nums = [3, -5, 4, -1, 2, 1, -6, 2]
    Output: 6             (the stretch [4, -1, 2, 1])

Example 2:
    Input:  nums = [-3, -1, -2]
    Output: -1            (the stretch can't be empty, so the best is [-1])

Example 3:
    Input:  nums = [5, -2, 7]
    Output: 10            (take everything: the -2 is worth bridging)

Constraints:
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

Target: O(n) time, O(1) extra space.
Follow-up: once you have the O(n) solution, try a divide-and-conquer one.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        throw NotImplemented();
    }
};
