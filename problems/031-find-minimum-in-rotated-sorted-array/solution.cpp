/*
31. Find Minimum in Rotated Sorted Array  ·  Medium  ·  Binary Search
Source: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

`nums` was a list of distinct integers sorted in increasing order, which was
then rotated between 1 and n times (n = nums.length). One rotation moves the
last element to the front:
    [a0, a1, ..., a(n-1)]  ->  [a(n-1), a0, a1, ..., a(n-2)]
so after n rotations the list is sorted again.

Return the smallest element of `nums`.

Your algorithm must run in O(log n) time. (One test calls findMin() over a
million times on 5000-element vectors, so a linear scan times out.)

Example 1:
    Input:  nums = [8, 11, 15, 2, 5]
    Output: 2

Example 2:
    Input:  nums = [-4, 0, 3, 9]
    Output: -4            (rotated n times: back in sorted order)

Example 3:
    Input:  nums = [6, 1]
    Output: 1

Constraints:
    1 <= nums.length <= 5000
    -5000 <= nums[i] <= 5000
    all values in nums are distinct
*/
#include "prelude.hpp"

class Solution {
public:
    int findMin(vector<int>& nums) {
        throw NotImplemented();
    }
};
