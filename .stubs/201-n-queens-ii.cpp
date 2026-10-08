/*
201. N-Queens II  ·  Hard  ·  Backtracking
Source: https://leetcode.com/problems/n-queens-ii/

Place n queens on an n x n chessboard so that no two of them attack each other:
no two queens may share a row, a column, or a diagonal (in either direction).
Return the number of different placements that achieve this.

Example 1:
    Input:  n = 4
    Output: 2             (.Q..    ..Q.
                           ...Q    Q...
                           Q...    ...Q
                           ..Q.    .Q..)

Example 2:
    Input:  n = 1
    Output: 1

Example 3:
    Input:  n = 3
    Output: 0

Constraints:
    1 <= n <= 9

Target: backtracking one row at a time, remembering which columns and which
diagonals (r - c and r + c) are taken, so each conflict check is O(1).
*/
#include "prelude.hpp"

class Solution {
public:
    int totalNQueens(int n) {
        throw NotImplemented();
    }
};
