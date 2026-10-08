/*
219. Minimum Path Sum  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/minimum-path-sum/

`grid` is an m x n grid of non-negative numbers. Walk from the top-left cell to
the bottom-right cell, moving only one cell right or one cell down at a time,
and add up the numbers of all the cells you visit (both ends included).
Return the smallest sum such a walk can have.

Example 1:
    Input:  grid = [[1, 4, 2],
                    [3, 1, 6],
                    [5, 2, 1]]
    Output: 8       (1 -> 3 -> 1 -> 2 -> 1: down, right, down, right)

Example 2:
    Input:  grid = [[7, 0, 9]]
    Output: 16

Example 3:
    Input:  grid = [[2, 9],
                    [1, 3],
                    [8, 0]]
    Output: 6       (2 -> 1 -> 3 -> 0)

Constraints:
    1 <= m, n <= 200        (m = grid.size(), n = grid[0].size())
    0 <= grid[i][j] <= 200

Target: O(m * n) time, O(n) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        throw NotImplemented();
    }
};
