/*
79. N-Queens  ·  Hard  ·  Backtracking
Source: https://leetcode.com/problems/n-queens/

Place n queens on an n x n chessboard so that no two of them attack each other:
no two queens may share a row, a column, or a diagonal (in either direction).
Return every such placement.

Each placement is a list of n strings, one per row from top to bottom; in each
string 'Q' marks a queen and '.' an empty square. Return the placements in any
order, each exactly once; return an empty list when there is no placement.

Example 1:
    Input:  n = 4
    Output: [[".Q..",
              "...Q",
              "Q...",
              "..Q."],
             ["..Q.",
              "Q...",
              "...Q",
              ".Q.."]]

Example 2:
    Input:  n = 1
    Output: [["Q"]]

Example 3:
    Input:  n = 3
    Output: []

Constraints:
    1 <= n <= 9

Target: backtracking one row at a time, remembering which columns and which
diagonals (r - c and r + c) are taken, so each conflict check is O(1).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        throw NotImplemented();
    }
};
