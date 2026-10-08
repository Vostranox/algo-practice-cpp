/*
195. Binary Tree Zigzag Level Order Traversal  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

Return the values of a binary tree grouped by level, one inner list per level
from the root level downwards, reading the levels in alternating directions:
the root's level left to right, the next one right to left, the one after
that left to right again, and so on. An empty tree gives [].

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [8, 4, 12, null, 6, 10, 14]
    Output: [[8], [12, 4], [6, 10, 14]]

Example 2:
    Input:  root = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    Output: [[1], [3, 2], [4, 5, 6, 7], [9, 8]]

Example 3:
    Input:  root = []
    Output: []

Constraints:
    0 <= number of nodes <= 2000
    -100 <= Node.val <= 100

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        throw NotImplemented();
    }
};
