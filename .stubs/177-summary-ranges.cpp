/*
177. Summary Ranges  ·  Easy  ·  Intervals
Source: https://leetcode.com/problems/summary-ranges/

You get a sorted array `nums` of distinct integers. Describe it as a list of
ranges of consecutive integers: every maximal run a, a + 1, ..., b of numbers
in `nums` becomes one entry, written as

    "a->b"   if a != b
    "a"      if a == b

Return the entries in increasing order. Every number of `nums` is covered by
exactly one range and no range covers a number missing from `nums`, so the
list is as short as possible. An empty array gives an empty list.

Example 1:
    Input:  nums = [0, 1, 2, 5, 7, 8]
    Output: ["0->2", "5", "7->8"]

Example 2:
    Input:  nums = [-3, -2, 4, 6, 7, 8, 10]
    Output: ["-3->-2", "4", "6->8", "10"]

Example 3:
    Input:  nums = []
    Output: []

Constraints:
    0 <= nums.length <= 20
    -2^31 <= nums[i] <= 2^31 - 1
    the values are distinct and sorted in increasing order

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        throw NotImplemented();
    }
};
