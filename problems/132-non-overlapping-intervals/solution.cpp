/*
132. Non-overlapping Intervals  ·  Medium  ·  Intervals
Source: https://leetcode.com/problems/non-overlapping-intervals/

You get an array of intervals [start, end] with start < end. Two intervals
overlap when they have a stretch of positive length in common; intervals that
merely touch, like [1, 2] and [2, 3], do NOT overlap. Return the smallest
number of intervals you must delete so that no two of the remaining ones
overlap.

Example 1:
    Input:  intervals = [[1, 3], [2, 4], [3, 5], [1, 5]]
    Output: 2             (keep [1, 3] and [3, 5])

Example 2:
    Input:  intervals = [[0, 2], [2, 4], [4, 6]]
    Output: 0             (they only touch)

Example 3:
    Input:  intervals = [[5, 9], [5, 9], [5, 9]]
    Output: 2

Constraints:
    1 <= intervals.length <= 10^5
    intervals[i] = [start_i, end_i] with -5 * 10^4 <= start_i < end_i <= 5 * 10^4

Target: O(n log n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        throw NotImplemented();
    }
};
