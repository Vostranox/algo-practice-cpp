/*
130. Insert Interval  ·  Medium  ·  Intervals
Source: https://leetcode.com/problems/insert-interval/

`intervals` is an array of closed intervals [start, end] (both ends included),
sorted by start, where no two intervals share a point (each one ends strictly
before the next one starts). Insert `newInterval` = [start, end] into it:
merge it with every interval it shares at least one point with - touching at
an endpoint counts - so the result again consists of sorted intervals that
share no points. Return the resulting intervals, sorted by start. You may
build and return a new array.

Example 1:
    Input:  intervals = [[1, 2], [5, 8], [10, 12]], newInterval = [6, 11]
    Output: [[1, 2], [5, 12]]

Example 2:
    Input:  intervals = [[1, 3], [6, 7]], newInterval = [4, 5]
    Output: [[1, 3], [4, 5], [6, 7]]     ([1, 3] and [4, 5] share no point)

Example 3:
    Input:  intervals = [[1, 3], [7, 9]], newInterval = [3, 7]
    Output: [[1, 9]]                     (shared endpoints 3 and 7 merge everything)

Constraints:
    0 <= intervals.length <= 10^4
    intervals[i] = [start_i, end_i] with 0 <= start_i <= end_i <= 10^5
    intervals is sorted by start_i and no two intervals share a point
    newInterval = [start, end] with 0 <= start <= end <= 10^5

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        throw NotImplemented();
    }
};
