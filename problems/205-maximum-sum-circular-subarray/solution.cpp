/*
205. Maximum Sum Circular Subarray  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/maximum-sum-circular-subarray/

`nums` is circular: after its last element comes its first element again.
Choose a non-empty contiguous stretch of it (it may wrap around from the end
back to the start) and return the largest possible sum. A stretch may not use
any element twice, so it is at most the whole array.

Example 1:
    Input:  nums = [6, -9, 1, 7]
    Output: 14       (wrap around: [1, 7, 6])

Example 2:
    Input:  nums = [-2, 4, 5, -3]
    Output: 9        ([4, 5], no wrapping needed)

Example 3:
    Input:  nums = [-4, -2, -7]
    Output: -2       (the stretch can't be empty, so the best is [-2])

Constraints:
    1 <= nums.length <= 3 * 10^4
    -3 * 10^4 <= nums[i] <= 3 * 10^4

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        throw NotImplemented();
    }
};
