/*
186. Construct Binary Tree from Inorder and Postorder Traversal  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

You get two arrays describing the same binary tree, whose values are all
distinct:
    inorder   — the values in inorder   (left subtree, then the node, then its right subtree)
    postorder — the values in postorder (left subtree, then its right subtree, then the node)
Rebuild the tree and return its root. (The two orders always determine the
tree uniquely.)

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Return a
TreeNode*; TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  inorder = [2, 4, 6, 10, 15, 20], postorder = [2, 6, 4, 20, 15, 10]
    Output: [10, 4, 15, 2, 6, null, 20]

Example 2:
    Input:  inorder = [1, 2, 3], postorder = [1, 2, 3]
    Output: [3, 2, null, 1]    (a chain of left children)

Example 3:
    Input:  inorder = [-1], postorder = [-1]
    Output: [-1]

Constraints:
    1 <= inorder.length <= 3000
    postorder.length == inorder.length
    -3000 <= inorder[i], postorder[i] <= 3000
    all values are distinct, and the arrays are valid traversals of one tree

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        throw NotImplemented();
    }
};
