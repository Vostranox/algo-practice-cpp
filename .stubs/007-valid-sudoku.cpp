/*
7. Valid Sudoku  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/valid-sudoku/

You get a 9 x 9 Sudoku board: board[r][c] is a digit '1'-'9' for a filled
cell or '.' for an empty one. Return true if the filled cells break none of
these rules, otherwise false:

    1. no digit appears twice in the same row,
    2. no digit appears twice in the same column,
    3. no digit appears twice in the same 3 x 3 box (the nine boxes are rows
       0-2/3-5/6-8 crossed with columns 0-2/3-5/6-8).

Only the filled cells are checked. A board can be valid even if it is
partially filled, and even if it could never be completed to a full solution.

Example 1:
    Input:  board (one string per row, '.' = empty)
        "3...84.27"
        ".7265..1."
        "..1..9.65"
        "..7.9...3"
        "..87.2.59"
        ".95.3.2.."
        ".2936.741"
        "7..92...."
        "....175.."
    Output: true

Example 2:
    Input:  the board from example 1 with board[0][1] = '1'
    Output: false         (row 0 and column 1 are still fine, but the top-left
                           box now holds two 1s: at [0][1] and [2][2])

Example 3:
    Input:  a board where every cell is '.'
    Output: true

Constraints:
    board.length == 9, board[i].length == 9
    board[i][j] is '1'-'9' or '.'
*/
#include "prelude.hpp"

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        throw NotImplemented();
    }
};
