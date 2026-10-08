/*
81. Clone Graph  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/clone-graph/

You get a pointer to one node of a connected, undirected graph. Return a deep
copy of the whole graph: one brand-new node per original node, with the same
value and the same neighbour list (same order), where every neighbour pointer
points to a new node. The copy must not contain any original node, and the
original graph must be left unchanged. Return the copy of the node you were
given; for nullptr (an empty graph) return nullptr.

Node has `int val` and `vector<Node*> neighbors`; create nodes with
new Node(val) or new Node(val, neighbors). An undirected edge u-v appears as v
in u->neighbors and as u in v->neighbors.

The examples (and the test messages) describe a graph as an adjacency list:
adj[i] lists the values of the neighbours of the node whose value is i + 1.
Values are 1..n and the node you receive is the one with value 1.

Example 1:
    Input:  adj = [[2, 3], [1, 3], [1, 2]]        (a triangle)
    Output: a copy whose adjacency list is [[2, 3], [1, 3], [1, 2]]

Example 2:
    Input:  adj = [[2], [1, 3], [2, 4], [3]]      (the path 1-2-3-4)
    Output: [[2], [1, 3], [2, 4], [3]]

Example 3:
    Input:  adj = [[]]                            (a single node, no edges)
    Output: [[]]

Constraints:
    0 <= number of nodes <= 100
    1 <= Node.val <= 100, all values distinct (they are 1..n)
    no repeated edges and no self-loops; the graph is connected

Target: O(V + E) time.
*/
#include "prelude.hpp"
using Node = GraphNode;

class Solution {
public:
    Node* cloneGraph(Node* node) {
        throw NotImplemented();
    }
};
