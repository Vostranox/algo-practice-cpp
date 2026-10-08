/*
178. Minimum Number of Arrows to Burst Balloons  ·  Medium  ·  Intervals
Source: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/

Balloons are taped to a wall. Seen from below, balloon i covers the closed
range points[i] = [x_start, x_end] of x-coordinates. An arrow shot straight up
from position x flies forever and bursts every balloon with
x_start <= x <= x_end (touching an end counts). Return the smallest number of
arrows needed to burst all the balloons.

Example 1:
    Input:  points = [[3, 7], [1, 4], [8, 12], [6, 9]]
    Output: 2             (e.g. x = 4 bursts [1, 4] and [3, 7]; x = 9 bursts the other two)

Example 2:
    Input:  points = [[1, 2], [3, 4], [5, 6]]
    Output: 3

Example 3:
    Input:  points = [[1, 3], [3, 5], [5, 7]]
    Output: 2             (x = 3 bursts the first two, which share the point 3)

Constraints:
    1 <= points.length <= 10^5
    points[i].length == 2
    -2^31 <= x_start < x_end <= 2^31 - 1

Target: O(n log n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        throw NotImplemented();
    }
};
