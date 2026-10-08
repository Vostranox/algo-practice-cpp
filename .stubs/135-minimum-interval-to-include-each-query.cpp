/*
135. Minimum Interval to Include Each Query  ·  Hard  ·  Intervals
Source: https://leetcode.com/problems/minimum-interval-to-include-each-query/

`intervals` holds closed intervals [left, right] (both ends included); the
size of an interval is the number of integers in it, right - left + 1.
For every number q in `queries`, find the smallest size among the intervals
that contain q (left <= q <= right), or -1 if no interval contains q.
Return the answers in the same order as `queries`.

Example 1:
    Input:  intervals = [[2, 5], [3, 3], [1, 8], [6, 7]], queries = [3, 6, 9, 1]
    Output: [1, 2, -1, 8]
            3 lies in [2, 5] (size 4), [3, 3] (size 1) and [1, 8] (size 8) -> 1
            6 lies in [1, 8] and [6, 7] -> 2;  nothing contains 9 -> -1;
            only [1, 8] contains 1 -> 8

Example 2:
    Input:  intervals = [[4, 4], [10, 20]], queries = [4, 5, 15, 10]
    Output: [1, -1, 11, 11]

Constraints:
    1 <= intervals.length <= 10^5
    1 <= queries.length <= 10^5
    intervals[i] = [left_i, right_i] with 1 <= left_i <= right_i <= 10^7
    1 <= queries[j] <= 10^7

Target: O((n + q) log(n + q)) time. Checking every interval for every query is
far too slow at these sizes.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        throw NotImplemented();
    }
};
