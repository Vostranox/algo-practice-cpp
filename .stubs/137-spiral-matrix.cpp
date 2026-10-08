/*
137. Spiral Matrix  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/spiral-matrix/

Given an m x n grid `matrix` (m rows, n columns, not necessarily square),
return all of its elements in clockwise spiral order: start at the top-left
cell, go right along the top row, then down the right-most column, then left
along the bottom row, then up the left-most column, and keep circling inwards
the same way until every cell has been listed exactly once.

Example 1:
    Input:  matrix = [[ 2,  4,  6],
                      [ 8, 10, 12],
                      [14, 16, 18]]
    Output: [2, 4, 6, 12, 18, 16, 14, 8, 10]

Example 2:
    Input:  matrix = [[ 1,  2,  3, 4],
                      [10, 11, 12, 5],
                      [ 9,  8,  7, 6]]
    Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

Example 3:
    Input:  matrix = [[7], [8], [9]]
    Output: [7, 8, 9]       (a single column is read top to bottom)

Constraints:
    m == matrix.length, n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        throw NotImplemented();
    }
};
