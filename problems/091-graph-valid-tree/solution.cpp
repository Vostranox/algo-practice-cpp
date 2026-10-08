/*
91. Graph Valid Tree  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/graph-valid-tree/

A graph has n nodes labelled 0 .. n - 1, and `edges` lists its undirected
edges as pairs {a, b}. Return true if these edges form a valid tree: every
node is reachable from every other node and there is no cycle. Otherwise
return false.

Example 1:
    Input:  n = 5, edges = [[0, 1], [0, 2], [2, 3], [2, 4]]
    Output: true

Example 2:
    Input:  n = 4, edges = [[0, 1], [1, 2], [2, 3], [1, 3]]
    Output: false       (1-2-3 is a cycle)

Example 3:
    Input:  n = 4, edges = [[0, 1], [2, 3]]
    Output: false       (two separate pieces)

Constraints:
    1 <= n <= 2000
    0 <= edges.length <= 5000
    edges[i].size() == 2,  0 <= a, b < n,  a != b
    no repeated edges

Target: O(n + edges.length) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        throw NotImplemented();
    }
};
