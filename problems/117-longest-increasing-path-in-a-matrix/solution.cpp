/*
117. Longest Increasing Path in a Matrix  ·  Hard  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

`matrix` is an m x n grid of integers. A path moves from a cell to one of its
up to four neighbours (up, down, left, right; no diagonals, no wrapping around
the edges), and every step must go to a strictly larger value. Return the
number of cells on the longest such path. A single cell is a path of length 1.

Example 1:
    Input:  matrix = [[1, 2, 3],
                      [6, 5, 4],
                      [7, 8, 9]]
    Output: 9          (1 -> 2 -> ... -> 9, snaking through the grid)

Example 2:
    Input:  matrix = [[9, 1],
                      [3, 2]]
    Output: 4          (1 -> 2 -> 3 -> 9)

Example 3:
    Input:  matrix = [[5, 5],
                      [5, 5]]
    Output: 1          (equal values don't count as increasing)

Constraints:
    1 <= m, n <= 200
    0 <= matrix[i][j] <= 2^31 - 1

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        throw NotImplemented();
    }
};
