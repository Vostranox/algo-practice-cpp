/*
138. Set Matrix Zeroes  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/set-matrix-zeroes/

You are given an m x n grid of integers `matrix`. Wherever the ORIGINAL grid
has a 0, the whole row and the whole column of that cell must become 0.
Zeros that you write while doing this do not spread any further: only the
zeros present before the call decide which rows and columns are cleared.

Modify `matrix` in place; the function returns nothing.

Example 1:
    Input:  matrix = [[3, 0, 5],
                      [2, 7, 1],
                      [4, 6, 8]]
    After:  matrix = [[0, 0, 0],
                      [2, 0, 1],
                      [4, 0, 8]]

Example 2:
    Input:  matrix = [[1,  2,  3, 4],
                      [5,  0,  7, 8],
                      [9, 10, 11, 0]]
    After:  matrix = [[1, 0, 3, 0],
                      [0, 0, 0, 0],
                      [0, 0, 0, 0]]

Example 3:
    Input:  matrix = [[0, 1, 2],
                      [3, 4, 5]]
    After:  matrix = [[0, 0, 0],
                      [0, 4, 5]]

Constraints:
    m == matrix.length, n == matrix[0].length
    1 <= m, n <= 200
    -2^31 <= matrix[i][j] <= 2^31 - 1

Target: O(m * n) time.
Follow-up: O(m * n) extra space is the obvious approach and O(m + n) is easy;
can you do it with O(1) extra space?
*/
#include "prelude.hpp"

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        throw NotImplemented();
    }
};
