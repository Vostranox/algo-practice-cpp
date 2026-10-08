/*
94. Min Cost to Connect All Points  ·  Medium  ·  Advanced Graphs
Source: https://leetcode.com/problems/min-cost-to-connect-all-points/

You get distinct points on a plane, points[i] = {x, y}. Linking two points
costs their Manhattan distance |x1 - x2| + |y1 - y2|. Choose links so that
every point can reach every other point through them, and return the minimum
possible total cost (this is the weight of a minimum spanning tree).

Example 1:
    Input:  points = [[0, 0], [3, 0], [3, 4], [10, 4]]
    Output: 14      (links of cost 3, 4 and 7)

Example 2:
    Input:  points = [[1, 1], [-1, -1], [1, -1]]
    Output: 4       (two links of cost 2)

Example 3:
    Input:  points = [[5, -7]]
    Output: 0       (nothing to connect)

Constraints:
    1 <= points.length <= 1000
    -10^6 <= x, y <= 10^6
    all points are distinct

Target: O(n^2) time (Prim's algorithm on the complete graph), or O(n^2 log n).
*/
#include "prelude.hpp"

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        throw NotImplemented();
    }
};
