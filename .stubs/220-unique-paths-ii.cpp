/*
220. Unique Paths II  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/unique-paths-ii/

A robot starts in the top-left cell of the m x n grid `obstacleGrid` and wants
to reach the bottom-right cell, moving one cell right or one cell down at a
time. A cell holding 1 is an obstacle the robot can't enter; a cell holding 0
is free. Return the number of different routes. (When the start or the target
cell is an obstacle there are none.)

Example 1:
    Input:  obstacleGrid = [[0, 0, 0, 0],
                            [0, 1, 0, 0],
                            [0, 0, 0, 0]]
    Output: 4       (10 routes without the obstacle, 6 of them pass through it)

Example 2:
    Input:  obstacleGrid = [[0, 1],
                            [1, 0]]
    Output: 0

Example 3:
    Input:  obstacleGrid = [[0, 0, 0, 0, 0]]
    Output: 1

Constraints:
    1 <= m, n <= 100        (m = obstacleGrid.size(), n = obstacleGrid[0].size())
    obstacleGrid[i][j] is 0 or 1
    the answer is at most 2 * 10^9. These tests also keep the number of routes
    from the start to any cell, and from any cell to the target, within that
    bound, so a table of ints never overflows.

Target: O(m * n) time, O(n) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        throw NotImplemented();
    }
};
