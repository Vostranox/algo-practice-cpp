/*
83. Pacific Atlantic Water Flow  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/pacific-atlantic-water-flow/

An m x n island is described by `heights`, the height of each cell. The
Pacific Ocean lies along the island's top and left edges, the Atlantic Ocean
along its bottom and right edges.

Rain water on a cell can flow to an up/down/left/right neighbour whose height
is less than or equal to the current cell's height, and so on from there. Water
on a cell in the top row or left column can drain into the Pacific; water on a
cell in the bottom row or right column can drain into the Atlantic.

Return every cell {r, c} from which water can reach BOTH oceans, in any order.

Example 1:
    Input:  heights = [[1, 2, 3],
                       [8, 9, 4],
                       [7, 6, 5]]
    Output: [[0, 2], [1, 0], [1, 1], [1, 2], [2, 0], [2, 1], [2, 2]]
            ((0, 0) and (0, 1) are lower than all their inner neighbours, so
            their water can only go to the Pacific)

Example 2:
    Input:  heights = [[1, 2],
                       [4, 3]]
    Output: [[0, 1], [1, 0], [1, 1]]

Example 3:
    Input:  heights = [[5]]
    Output: [[0, 0]]

Constraints:
    1 <= m, n <= 200
    0 <= heights[r][c] <= 10^5

Target: O(m * n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        throw NotImplemented();
    }
};
