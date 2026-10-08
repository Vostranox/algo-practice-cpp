/*
86. Walls and Gates  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/walls-and-gates/

You get an m x n grid `rooms` where each cell is one of
    -1             a wall
     0             a gate
    2147483647     an empty room (INF = 2^31 - 1 = INT_MAX)
Fill every empty room with the number of steps to its nearest gate, where a
step moves up/down/left/right into a cell that is not a wall. A room from
which no gate can be reached keeps the value INF. Walls and gates stay as
they are.

Modify `rooms` in place; the function returns nothing.

Example 1 (INF = 2147483647):
    Input:  rooms = [[INF, INF,   0],
                     [INF,  -1, INF],
                     [  0, INF, INF]]
    After:  rooms = [[2,  1, 0],
                     [1, -1, 1],
                     [0,  1, 2]]

Example 2:
    Input:  rooms = [[  0, -1, INF],
                     [INF, -1, INF]]
    After:  rooms = [[0, -1, INF],
                     [1, -1, INF]]      (the right column is walled off)

Example 3:
    Input:  rooms = [[INF, INF, INF, 0]]
    After:  rooms = [[3, 2, 1, 0]]

Constraints:
    1 <= m, n <= 250
    rooms[i][j] is -1, 0 or 2147483647

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        throw NotImplemented();
    }
};
