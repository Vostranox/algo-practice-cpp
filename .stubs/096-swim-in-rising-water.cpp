/*
96. Swim in Rising Water  ·  Hard  ·  Advanced Graphs
Source: https://leetcode.com/problems/swim-in-rising-water/

An n x n grid gives the elevation of each square; the values are all distinct
and are exactly 0 .. n^2 - 1. Rain makes the water level equal to t at time t.
At time t you can swim from a square to an up/down/left/right neighbour if both
squares have elevation <= t; swimming itself takes no time. You start at the
top-left square (0, 0). Return the smallest time t at which you can reach the
bottom-right square (n - 1, n - 1).

Example 1:
    Input:  grid = [[0, 3],
                    [1, 2]]
    Output: 2       (0 -> 1 -> 2 down the left side, then right)

Example 2:
    Input:  grid = [[0, 1, 2],
                    [7, 8, 3],
                    [6, 5, 4]]
    Output: 4       (around the edge 0 1 2 3 4; you must wait for the target's 4 anyway)

Example 3:
    Input:  grid = [[0, 5, 1],
                    [2, 8, 3],
                    [7, 6, 4]]
    Output: 5       (squares up to 4 don't connect start and target; at 5 the top row opens)

Constraints:
    1 <= n <= 50
    grid[i][j] are the distinct values 0 .. n^2 - 1

Target: O(n^2 log n) time (Dijkstra-style search minimising the highest square on the path).
*/
#include "prelude.hpp"

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        throw NotImplemented();
    }
};
