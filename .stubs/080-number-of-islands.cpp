/*
80. Number of Islands  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/number-of-islands/

You get an m x n map `grid` whose cells are the characters '1' (land) and '0'
(water). An island is a maximal group of land cells joined through their
up/down/left/right neighbours (cells touching only diagonally are NOT joined).
Everything outside the map is water. Return the number of islands.

You may modify `grid` while solving (e.g. to mark cells as visited).

Example 1:
    Input:  grid = [['1','1','0','0'],
                    ['0','1','0','1'],
                    ['0','0','0','1'],
                    ['1','0','1','1']]
    Output: 3       (top-left group, right-hand group, lone cell bottom-left)

Example 2:
    Input:  grid = [['1','0','1'],
                    ['0','1','0'],
                    ['1','0','1']]
    Output: 5       (diagonal neighbours are not connected)

Example 3:
    Input:  grid = [['0','0'],
                    ['0','0']]
    Output: 0

Constraints:
    1 <= m, n <= 300        (m = grid.size(), n = grid[0].size())
    grid[i][j] is '0' or '1'

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        throw NotImplemented();
    }
};
