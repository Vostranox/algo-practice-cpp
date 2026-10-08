/*
136. Rotate Image  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/rotate-image/

You are given a square n x n grid of integers `matrix`. Rotate it a quarter
turn (90 degrees) clockwise: the old top row becomes the new right-most column
(read top to bottom), the old left-most column becomes the new top row (read
right to left), and so on.

The rotation must happen in place: change the values inside `matrix` itself
and don't allocate a second n x n matrix for the answer. The function returns
nothing.

Example 1:
    Input:  matrix = [[1, 2],
                      [3, 4]]
    After:  matrix = [[3, 1],
                      [4, 2]]

Example 2:
    Input:  matrix = [[ 5,  1,  9],
                      [ 2,  4,  8],
                      [13,  3,  6]]
    After:  matrix = [[13,  2,  5],
                      [ 3,  4,  1],
                      [ 6,  8,  9]]

Example 3:
    Input:  matrix = [[-7]]
    After:  matrix = [[-7]]      (a 1 x 1 grid looks the same after any rotation)

Constraints:
    n == matrix.length == matrix[i].length
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000

Target: O(n^2) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        throw NotImplemented();
    }
};
