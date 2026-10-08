/*
9. Longest Consecutive Sequence  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/longest-consecutive-sequence/

You get an unsorted integer array `nums`. Return the length of the longest
run of consecutive integers x, x+1, x+2, ..., x+L-1 that are ALL present in
`nums`. Their positions in the array don't matter, and repeated values count
only once. An empty array gives 0.

Your algorithm must run in O(n) time.

Example 1:
    Input:  nums = [7, 50, 5, 6, 100, 4, 8]
    Output: 5             (4, 5, 6, 7, 8)

Example 2:
    Input:  nums = [0, -1, 1, 1, -2, 9]
    Output: 4             (-2, -1, 0, 1; the second 1 adds nothing)

Example 3:
    Input:  nums = []
    Output: 0

Constraints:
    0 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

Target: O(n) time (sorting would be O(n log n)).
*/
#include "prelude.hpp"

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        throw NotImplemented();
    }
};
