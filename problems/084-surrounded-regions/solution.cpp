/*
84. Surrounded Regions  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/surrounded-regions/

You get an m x n board of the characters 'X' and 'O'. A region is a maximal
group of 'O' cells connected through up/down/left/right neighbours. A region
is captured when none of its cells lies on the outer border of the board (it is
completely enclosed by 'X'). Capture every such region by turning all of its
cells into 'X'. Regions with at least one cell on the border stay as they are.

Modify `board` in place; the function returns nothing.

Example 1:
    Input:  board = [['O','X','X','O'],
                     ['X','O','O','X'],
                     ['X','O','X','X'],
                     ['O','X','O','X']]
    After:  board = [['O','X','X','O'],
                     ['X','X','X','X'],
                     ['X','X','X','X'],
                     ['O','X','O','X']]
            (the three inner 'O's are enclosed; the others are on the border)

Example 2:
    Input:  board = [['X','X','X','X','X'],
                     ['X','O','O','O','X'],
                     ['X','O','X','O','X'],
                     ['X','O','O','O','X'],
                     ['X','X','X','X','X']]
    After:  every cell is 'X'

Example 3:
    Input:  board = [['X','O','X'],
                     ['X','O','X'],
                     ['X','X','X']]
    After:  unchanged  (the inner 'O' is joined to an 'O' on the top border)

Constraints:
    1 <= m, n <= 200
    board[i][j] is 'X' or 'O'

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        throw NotImplemented();
    }
};
