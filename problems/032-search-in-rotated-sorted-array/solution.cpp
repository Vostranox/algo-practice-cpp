/*
32. Search in Rotated Sorted Array  ·  Medium  ·  Binary Search
Source: https://leetcode.com/problems/search-in-rotated-sorted-array/

`nums` was a list of distinct integers sorted in increasing order, which was
then possibly rotated at some unknown point k (0 <= k < n): it became
    [a(k), a(k+1), ..., a(n-1), a(0), a(1), ..., a(k-1)]
(k = 0 means it was left sorted).

Return the index of `target` in `nums`, or -1 if it is not there.

Your algorithm must run in O(log n) time. (One test calls search() over a
million times on 5000-element vectors, so a linear scan times out.)

Example 1:
    Input:  nums = [12, 15, 19, 1, 4, 7], target = 4
    Output: 4

Example 2:
    Input:  nums = [12, 15, 19, 1, 4, 7], target = 13
    Output: -1

Example 3:
    Input:  nums = [3, 5, 8], target = 3
    Output: 0             (not rotated)

Constraints:
    1 <= nums.length <= 5000
    -10^4 <= nums[i], target <= 10^4
    all values in nums are distinct
*/
#include "prelude.hpp"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        throw NotImplemented();
    }
};
