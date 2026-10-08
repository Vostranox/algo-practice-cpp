/*
172. Game of Life  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/game-of-life/

Conway's Game of Life is played on an m x n grid `board` in which every cell is
alive (1) or dead (0). A cell's neighbours are the up to eight cells touching it
horizontally, vertically or diagonally; positions outside the board count as
dead. One step of the game turns the board into the next generation:

    a live cell with fewer than 2 live neighbours dies
    a live cell with 2 or 3 live neighbours stays alive
    a live cell with more than 3 live neighbours dies
    a dead cell with exactly 3 live neighbours becomes alive (otherwise it stays dead)

All cells change at the same moment: every cell's fate is decided by the board
as it was BEFORE the step, never by values already updated during it.

Advance `board` by one step, in place; the function returns nothing.

Example 1:
    Input:  board = [[0, 1, 0],
                     [0, 1, 0],
                     [0, 1, 0]]
    After:  board = [[0, 0, 0],
                     [1, 1, 1],
                     [0, 0, 0]]     (the vertical bar becomes a horizontal one)

Example 2:
    Input:  board = [[1, 0, 0, 1],
                     [0, 1, 1, 0],
                     [1, 0, 0, 0]]
    After:  board = [[0, 1, 1, 0],
                     [1, 1, 1, 0],
                     [0, 1, 0, 0]]

Example 3:
    Input:  board = [[1, 1],
                     [1, 1]]
    After:  board = [[1, 1],
                     [1, 1]]        (each cell has 3 live neighbours: nothing changes)

Constraints:
    m == board.length, n == board[i].length
    1 <= m, n <= 25
    board[i][j] is 0 or 1

Target: O(m * n) time.
Follow-up: copying the board makes the simultaneous update easy; can you do it
with O(1) extra space? (honor system: the tests can't tell.) And how would you
handle a board that is unbounded, where live cells can wander arbitrarily far?
*/
#include "prelude.hpp"

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        throw NotImplemented();
    }
};
