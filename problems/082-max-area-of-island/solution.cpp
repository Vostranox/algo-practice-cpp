/*
82. Max Area of Island  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/max-area-of-island/

You get an m x n grid of integers, 1 for land and 0 for water. An island is a
maximal group of land cells connected through up/down/left/right neighbours
(diagonal contact does not count). The area of an island is its number of
cells. Return the largest island area, or 0 if there is no land at all.

You may modify `grid` while solving.

Example 1:
    Input:  grid = [[1, 1, 0, 0, 0],
                    [1, 0, 0, 1, 1],
                    [0, 0, 1, 1, 0],
                    [0, 1, 0, 1, 0]]
    Output: 5       (islands of area 3, 5 and 1)

Example 2:
    Input:  grid = [[1, 0, 1],
                    [0, 1, 0]]
    Output: 1       (three separate one-cell islands)

Example 3:
    Input:  grid = [[0, 0],
                    [0, 0]]
    Output: 0

Constraints:
    1 <= m, n <= 50
    grid[i][j] is 0 or 1

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        throw NotImplemented();
    }
};
