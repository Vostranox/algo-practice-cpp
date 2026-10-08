/*
52. Lowest Common Ancestor of a Binary Search Tree  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

You get the root of a binary search tree (every value in a node's left subtree
is smaller than the node's value, every value in its right subtree is larger)
and two different nodes p and q of that tree. Return their lowest common
ancestor: the deepest node that has both p and q in its subtree. A node counts
as being in its own subtree, so if p is an ancestor of q the answer is p.

p and q are pointers to nodes of the tree (written as their values below), and
you must return a pointer to the answer node itself, not to a copy.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [20, 10, 30, 5, 15, 25, 35], p = 5, q = 15
    Output: 10

Example 2:
    Input:  root = [20, 10, 30, 5, 15, 25, 35], p = 10, q = 15
    Output: 10            (p is an ancestor of q)

Example 3:
    Input:  root = [20, 10, 30, 5, 15, 25, 35], p = 35, q = 5
    Output: 20

Constraints:
    2 <= number of nodes <= 10^5
    -10^9 <= Node.val <= 10^9, all values distinct
    p != q, and both are in the tree

Target: O(h) time per call (h = height of the tree) by following the BST
ordering instead of searching the whole tree; the tests make many calls on a
big tree. O(1) extra space is possible.
*/
#include "prelude.hpp"

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        throw NotImplemented();
    }
};
