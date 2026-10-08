/*
223. Maximal Square  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/maximal-square/

`matrix` is an m x n grid of the characters '0' and '1'. Find the largest
square block of cells (sides parallel to the grid) that contains only '1's,
and return its area, i.e. side * side. Return 0 if there is no '1' at all.

Example 1:
    Input:  matrix = [['1','1','0','1'],
                      ['1','1','1','1'],
                      ['0','1','1','1'],
                      ['1','1','1','1']]
    Output: 9       (rows 1-3, columns 1-3)

Example 2:
    Input:  matrix = [['0','1'],
                      ['1','0']]
    Output: 1

Example 3:
    Input:  matrix = [['0']]
    Output: 0

Constraints:
    1 <= m, n <= 300        (m = matrix.size(), n = matrix[0].size())
    matrix[i][j] is '0' or '1'

Target: O(m * n) time, O(n) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        throw NotImplemented();
    }
};
