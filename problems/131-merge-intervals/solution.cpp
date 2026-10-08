/*
131. Merge Intervals  ·  Medium  ·  Intervals
Source: https://leetcode.com/problems/merge-intervals/

You get an array of closed intervals [start, end] (both ends included), in no
particular order. Merge every group of intervals that overlap - two intervals
overlap when they share at least one point, so [1, 3] and [3, 5] merge into
[1, 5], while [1, 2] and [3, 4] stay apart. Return the merged intervals sorted
by start; together they must cover exactly the points covered by the input,
and no two of them may share a point.

Example 1:
    Input:  intervals = [[8, 10], [1, 4], [2, 6], [12, 15]]
    Output: [[1, 6], [8, 10], [12, 15]]

Example 2:
    Input:  intervals = [[3, 5], [5, 9]]
    Output: [[3, 9]]                 (touching at 5 counts as overlapping)

Example 3:
    Input:  intervals = [[2, 3], [1, 10], [4, 4]]
    Output: [[1, 10]]

Constraints:
    1 <= intervals.length <= 10^4
    intervals[i] = [start_i, end_i] with 0 <= start_i <= end_i <= 10^4

Target: O(n log n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        throw NotImplemented();
    }
};
