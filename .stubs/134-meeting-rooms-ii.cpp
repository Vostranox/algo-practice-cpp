/*
134. Meeting Rooms II  ·  Medium  ·  Intervals
Source: https://leetcode.com/problems/meeting-rooms-ii/

Each element of `intervals` is a meeting [start, end] (start < end) that
occupies a room from time start until time end. A room is free again at the
moment its meeting ends, so a meeting ending at t and one starting at t can
use the same room. Return the smallest number of rooms that can host all the
meetings.

(Some versions of this problem pass Interval objects with .start and .end;
here it is a vector of [start, end] pairs.)

Example 1:
    Input:  intervals = [[1, 10], [2, 4], [5, 9], [4, 6]]
    Output: 3             (between 5 and 6, [1, 10], [5, 9] and [4, 6] all run)

Example 2:
    Input:  intervals = [[6, 8], [1, 3]]
    Output: 1

Example 3:
    Input:  intervals = [[1, 5], [5, 10], [10, 15]]
    Output: 1             (each meeting takes over the room as the previous one ends)

Constraints:
    1 <= intervals.length <= 10^4
    intervals[i] = [start_i, end_i] with 0 <= start_i < end_i <= 10^6

Target: O(n log n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        throw NotImplemented();
    }
};
