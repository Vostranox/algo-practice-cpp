/*
208. Find First and Last Position of Element in Sorted Array  ·  Medium  ·  Binary Search
Source: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

`nums` is sorted in non-decreasing order, so equal values sit next to each
other. Return [first, last]: the smallest and the largest index at which
`target` occurs. If target doesn't occur in nums, return [-1, -1].

Your algorithm must run in O(log n) time. (One test runs 3 * 10^5 searches on
10^5-element vectors with very long runs of equal values, so a linear scan, or
a binary search that then walks to both ends of the run, times out.)

Example 1:
    Input:  nums = [1, 3, 3, 3, 6, 9], target = 3
    Output: [1, 3]

Example 2:
    Input:  nums = [1, 3, 3, 3, 6, 9], target = 4
    Output: [-1, -1]

Example 3:
    Input:  nums = [], target = 0
    Output: [-1, -1]

Constraints:
    0 <= nums.length <= 10^5
    -10^9 <= nums[i], target <= 10^9
    nums is sorted in non-decreasing order
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        throw NotImplemented();
    }
};
