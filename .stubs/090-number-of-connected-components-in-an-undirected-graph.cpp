/*
90. Number of Connected Components in an Undirected Graph  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

A graph has n nodes labelled 0 .. n - 1, and `edges` lists its undirected
edges as pairs {a, b}. Return the number of connected components (groups of
nodes that are linked to each other through edges; a node without edges is a
component on its own).

Example 1:
    Input:  n = 6, edges = [[0, 1], [2, 3], [1, 4]]
    Output: 3       ({0, 1, 4}, {2, 3} and {5})

Example 2:
    Input:  n = 4, edges = [[0, 1], [1, 2], [2, 3], [3, 0]]
    Output: 1

Example 3:
    Input:  n = 3, edges = []
    Output: 3

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
    int countComponents(int n, vector<vector<int>>& edges) {
        throw NotImplemented();
    }
};
