/*
198. Snakes and Ladders  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/snakes-and-ladders/

`board` is an n x n game board. Its squares are numbered 1 to n^2 in zigzag
order: square 1 is the bottom-left cell board[n-1][0], the numbers run left to
right along the bottom row, then right to left along the row above it, then
left to right again, and so on, switching direction every row. For n = 4:

    board[0]:  16 15 14 13
    board[1]:   9 10 11 12
    board[2]:   8  7  6  5
    board[3]:   1  2  3  4

A cell holds -1 (an ordinary square) or the number of another square: the
square is then the start of a snake or ladder leading to that square.

You start on square 1. In one move you pick any target t from s + 1 to
min(s + 6, n^2), where s is your current square (you choose the die roll). If t
starts a snake or ladder you move on to its end square, otherwise you stay on
t. A move follows at most one snake or ladder: when its end square starts
another one, you stop there anyway (but landing on that square with a later
roll does use it).

Return the fewest moves needed to reach square n^2, or -1 if it can't be
reached.

Example 1:
    Input:  board = [[-1, -1, -1, -1],
                     [-1, -1, -1,  2],
                     [-1, -1, -1, -1],
                     [-1, -1, 15, -1]]
    Output: 2       (roll 2: square 3 has a ladder to 15; then roll 1: square 16)

Example 2:
    Input:  board = [[-1, -1, -1, -1],
                     [16, -1, -1, -1],
                     [-1, -1, -1, -1],
                     [-1,  9, -1, -1]]
    Output: 2       (the ladder 2 -> 9 does not continue up the ladder 9 -> 16 in
                     the same move; instead go to 7, then roll a 2 onto 9 and climb to 16)

Example 3:
    Input:  board = [[ 1, -1, -1],
                     [ 1,  1,  1],
                     [-1,  1,  1]]
    Output: -1      (squares 2 to 7 all lead back to square 1)

Constraints:
    n == board.length == board[i].length,  2 <= n <= 20
    board[i][j] is -1 or a square number from 1 to n^2
    squares 1 and n^2 never start a snake or ladder

Target: O(n^2) time (breadth-first search over squares).
*/
#include "prelude.hpp"

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        throw NotImplemented();
    }
};
