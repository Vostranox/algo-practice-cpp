/*
58. Construct Binary Tree from Preorder and Inorder Traversal  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

You get two arrays describing the same binary tree, whose values are all
distinct:
    preorder — the values in preorder (node, then its left subtree, then its right subtree)
    inorder  — the values in inorder  (left subtree, then the node, then its right subtree)
Rebuild the tree and return its root. (The two orders always determine the
tree uniquely.)

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Return a
TreeNode*; TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  preorder = [10, 4, 2, 6, 15, 20], inorder = [2, 4, 6, 10, 15, 20]
    Output: [10, 4, 15, 2, 6, null, 20]

Example 2:
    Input:  preorder = [1, 2, 3], inorder = [3, 2, 1]
    Output: [1, 2, null, 3]    (a chain of left children)

Example 3:
    Input:  preorder = [-1], inorder = [-1]
    Output: [-1]

Constraints:
    1 <= preorder.length <= 3000
    inorder.length == preorder.length
    -3000 <= preorder[i], inorder[i] <= 3000
    all values are distinct, and the arrays are valid traversals of one tree

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        throw NotImplemented();
    }
};
