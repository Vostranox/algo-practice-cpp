/*
53. Binary Tree Level Order Traversal  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/binary-tree-level-order-traversal/

Return the values of a binary tree grouped by level: one inner list per level,
from the root level downwards, each holding that level's values from left to
right. An empty tree gives [].

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [8, 4, 12, null, 6, 10]
    Output: [[8], [4, 12], [6, 10]]

Example 2:
    Input:  root = [1, 2, null, 3, null, 4]
    Output: [[1], [2], [3], [4]]

Example 3:
    Input:  root = []
    Output: []

Constraints:
    0 <= number of nodes <= 2000
    -1000 <= Node.val <= 1000

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        throw NotImplemented();
    }
};
