/*
193. Lowest Common Ancestor of a Binary Tree  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

You get the root of a binary tree (not a search tree: the values are in no
particular order) and two different nodes p and q of that tree. Return their
lowest common ancestor: the deepest node that has both p and q in its
subtree. A node counts as being in its own subtree, so if p is an ancestor of
q the answer is p.

p and q are pointers to nodes of the tree (written as their values below), and
you must return a pointer to the answer node itself, not to a copy.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [10, 4, 7, 9, 2, null, 5, null, null, 8, 1], p = 9, q = 1
    Output: 4

Example 2:
    Input:  root = [10, 4, 7, 9, 2, null, 5, null, null, 8, 1], p = 2, q = 8
    Output: 2             (p is an ancestor of q)

Example 3:
    Input:  root = [10, 4, 7, 9, 2, null, 5, null, null, 8, 1], p = 8, q = 5
    Output: 10

Constraints:
    2 <= number of nodes <= 10^5
    -10^9 <= Node.val <= 10^9, all values distinct
    p != q, and both are in the tree

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        throw NotImplemented();
    }
};
