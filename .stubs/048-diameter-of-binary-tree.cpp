/*
48. Diameter of Binary Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/diameter-of-binary-tree/

The diameter of a binary tree is the length of the longest path between any
two of its nodes, measured in edges (a path of k nodes has length k - 1). The
path may or may not pass through the root. Return the diameter.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [6, 2, 9, 1, 4, null, null, null, null, 3]
    Output: 4             (3 -> 4 -> 2 -> 6 -> 9)

Example 2:
    Input:  root = [1, 2, null, 3, 4, 5, null, null, 6]
    Output: 4             (5 -> 3 -> 2 -> 4 -> 6; the root is not on it)

Example 3:
    Input:  root = [8]
    Output: 0

Constraints:
    1 <= number of nodes <= 10^4
    -100 <= Node.val <= 100

Target: O(n) time: compute each subtree's height only once.
*/
#include "prelude.hpp"

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        throw NotImplemented();
    }
};
