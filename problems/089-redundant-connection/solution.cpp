/*
89. Redundant Connection  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/redundant-connection/

A tree with n nodes, labelled 1..n, had exactly one extra edge added to it,
between two different nodes that were not already directly connected. You get
the resulting n undirected edges as edges[i] = {a, b} with a < b.

Return an edge whose removal turns the graph back into a tree on all n nodes
(i.e. an edge lying on the graph's only cycle). If several edges qualify,
return the one that appears LAST in `edges`. Return it as {a, b}, exactly as
it appears in the input.

Example 1:
    Input:  edges = [[1, 2], [2, 3], [3, 4], [1, 4], [1, 5]]
    Output: [1, 4]      (the cycle is 1-2-3-4-1; [1, 4] is its last edge in the list)

Example 2:
    Input:  edges = [[2, 3], [1, 3], [1, 2], [3, 4]]
    Output: [1, 2]

Example 3:
    Input:  edges = [[1, 4], [3, 4], [1, 3], [1, 2], [4, 5]]
    Output: [1, 3]

Constraints:
    n == edges.length,  3 <= n <= 1000
    edges[i].size() == 2,  1 <= a < b <= n
    no repeated edges; the graph is connected

Target: O(n * α(n)) time with union-find (O(n) per edge DFS also passes).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        throw NotImplemented();
    }
};
