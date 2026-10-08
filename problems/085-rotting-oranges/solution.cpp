/*
85. Rotting Oranges  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/rotting-oranges/

You get an m x n grid where each cell is
    0  empty
    1  a fresh orange
    2  a rotten orange
Every minute, each fresh orange that is up/down/left/right next to a rotten
orange becomes rotten (all such changes happen at the same time). Return the
number of minutes until no fresh orange is left, or -1 if some fresh orange can
never rot. If there are no fresh oranges at the start, the answer is 0.

Example 1:
    Input:  grid = [[2, 1, 1],
                    [0, 0, 1],
                    [1, 1, 1]]
    Output: 6       (the rot travels along the path, one cell per minute)

Example 2:
    Input:  grid = [[1, 0, 2]]
    Output: -1      (the fresh orange on the left is cut off)

Example 3:
    Input:  grid = [[0, 2]]
    Output: 0       (nothing is fresh)

Constraints:
    1 <= m, n <= 10
    grid[i][j] is 0, 1 or 2

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        throw NotImplemented();
    }
};
