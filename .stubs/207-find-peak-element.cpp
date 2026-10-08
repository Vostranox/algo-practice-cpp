/*
207. Find Peak Element  ·  Medium  ·  Binary Search
Source: https://leetcode.com/problems/find-peak-element/

A peak is an element that is strictly greater than each of its neighbours. You
get an integer array `nums` in which no two adjacent elements are equal. Treat
the positions just outside the array, nums[-1] and nums[n], as minus infinity
(smaller than every int, INT_MIN included), so the first and the last element
only have to beat their one real neighbour.

Return the index of a peak. There is always at least one; if there are several,
any of them is accepted.

Your algorithm must run in O(log n) time. (One test calls findPeakElement()
millions of times on 1000-element arrays whose only peak is in the back half,
so a linear scan from the front times out.)

Example 1:
    Input:  nums = [2, 7, 4, 1]
    Output: 1

Example 2:
    Input:  nums = [1, 5, 3, 4, 8, 6]
    Output: 1 or 4        (both 5 and 8 are peaks)

Example 3:
    Input:  nums = [9, 6, 2]
    Output: 0             (9 only has to beat 6)

Constraints:
    1 <= nums.length <= 1000
    -2^31 <= nums[i] <= 2^31 - 1
    nums[i] != nums[i + 1] for every valid i
*/
#include "prelude.hpp"

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        throw NotImplemented();
    }
};
