/*
204. Construct Quad Tree  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/construct-quad-tree/

You get an n x n grid of 0s and 1s, where n is a power of two. Build its quad
tree, in which every node stands for a square region of the grid (the root for
the whole grid):
    - if all cells of the region hold the same value, the node is a leaf:
      isLeaf = true, val = that value (true for 1, false for 0), and its four
      children are nullptr;
    - otherwise the node is internal: isLeaf = false, val can be either, and its
      four children are the quad trees of the four equal quarters of the
      region: topLeft, topRight, bottomLeft and bottomRight.
Return the root.

The node type Node (an alias of QuadNode from prelude.hpp) has bool val,
bool isLeaf and Node* topLeft, topRight, bottomLeft, bottomRight, with
constructors Node(), Node(val, isLeaf) and
Node(val, isLeaf, topLeft, topRight, bottomLeft, bottomRight).

Quad trees are shown as nodes in level order (a node's four children in the
order above), each one as [isLeaf, val] with 1/0, null for a missing child,
trailing nulls omitted.

Example 1:
    Input:  grid = [[1, 1],
                    [1, 1]]
    Output: [[1, 1]]       (one leaf holding 1)

Example 2:
    Input:  grid = [[1, 0],
                    [0, 1]]
    Output: [[0, 0], [1, 1], [1, 0], [1, 0], [1, 1]]
            (an internal root, whose val could also be 1, with four leaves)

Example 3:
    Input:  grid = [[1, 1, 0, 0],
                    [1, 1, 0, 0],
                    [1, 1, 0, 1],
                    [1, 1, 1, 1]]
    Output: root: internal
              topLeft:     leaf 1
              topRight:    leaf 0
              bottomLeft:  leaf 1
              bottomRight: internal, with leaves 0, 1, 1, 1
            i.e. [[0, 0], [1, 1], [1, 0], [1, 1], [0, 0], null, null, null, null,
                  null, null, null, null, null, null, null, null, [1, 0], [1, 1], [1, 1], [1, 1]]

Constraints:
    n == grid.length == grid[i].length
    n == 2^x with 0 <= x <= 6
    grid[i][j] is 0 or 1

Target: O(n^2) time.
*/
#include "prelude.hpp"

using Node = QuadNode;

class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        throw NotImplemented();
    }
};
