/*
49. Balanced Binary Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/balanced-binary-tree/

A binary tree is height-balanced when, at EVERY node, the heights of the left
and right subtrees differ by at most 1 (an empty subtree has height 0). Return
true if the given tree is height-balanced, false otherwise. An empty tree is
balanced.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [10, 5, 15, 2, 8, null, 20]
    Output: true

Example 2:
    Input:  root = [1, 2, 3, 4, null, null, 6, 5, null, null, 7]
    Output: false         (both subtrees of the root have height 3, but node 2
                           has a left subtree of height 2 and no right child)

Example 3:
    Input:  root = []
    Output: true

Constraints:
    0 <= number of nodes <= 5000
    -10^4 <= Node.val <= 10^4

Target: O(n) time: compute each subtree's height once.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        throw NotImplemented();
    }
};
