/*
133. Meeting Rooms  ·  Easy  ·  Intervals
Source: https://leetcode.com/problems/meeting-rooms/

Each element of `intervals` is a meeting [start, end] (start < end). Return
true if one person could attend all of them, i.e. no two meetings overlap,
otherwise false. A meeting that ends at time t does not conflict with one
that starts at time t.

(Some versions of this problem pass Interval objects with .start and .end;
here it is a vector of [start, end] pairs.)

Example 1:
    Input:  intervals = [[9, 12], [1, 4], [5, 8]]
    Output: true

Example 2:
    Input:  intervals = [[2, 7], [6, 9]]
    Output: false         (both run between 6 and 7)

Example 3:
    Input:  intervals = [[1, 5], [5, 6]]
    Output: true          (back-to-back is fine)

Constraints:
    0 <= intervals.length <= 10^4
    intervals[i] = [start_i, end_i] with 0 <= start_i < end_i <= 10^6

Target: O(n log n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        throw NotImplemented();
    }
};
