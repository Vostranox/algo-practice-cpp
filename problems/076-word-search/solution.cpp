/*
76. Word Search  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/word-search/

Given an m x n grid of letters `board` and a string `word`, return true if word
can be traced in the grid, otherwise false.

A trace starts at any cell and repeatedly steps to a horizontally or vertically
adjacent cell (no diagonals); the letters of the visited cells, in order, must
spell word. The same cell may not be used twice within one trace.

    board = [['S', 'E', 'A'],
             ['T', 'A', 'R'],
             ['O', 'N', 'E']]

Example 1:
    Input:  board (above), word = "STONE"
    Output: true       (down the left column, then along the bottom row)

Example 2:
    Input:  board (above), word = "RATS"
    Output: true       (R -> middle A -> T -> S)

Example 3:
    Input:  board (above), word = "TAT"
    Output: false      (the board has only one T, and a cell can't be used twice)

Constraints:
    m == board.length, n == board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    board and word contain only English letters, upper- or lower-case
    ('a' and 'A' are different letters)

Target: backtracking DFS from every cell, O(m * n * 3^word.length) in the worst case.
Follow-up: prune the search so hopeless inputs fail fast -- e.g. a board of
nothing but 'A's and the word "AAAAAAAAAAAAAAB".
*/
#include "prelude.hpp"

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        throw NotImplemented();
    }
};
