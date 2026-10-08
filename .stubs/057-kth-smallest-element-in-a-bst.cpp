/*
57. Kth Smallest Element in a BST  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/kth-smallest-element-in-a-bst/

You get the root of a binary search tree (every value in a node's left subtree
is smaller than the node's value, every value in its right subtree is larger)
and an integer k. Return the k-th smallest value in the tree, counting from 1
(k = 1 is the minimum).

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [6, 2, 8, 1, 4, 7, 9], k = 3
    Output: 4             (sorted values: 1, 2, 4, 6, 7, 8, 9)

Example 2:
    Input:  root = [6, 2, 8, 1, 4, 7, 9], k = 7
    Output: 9

Example 3:
    Input:  root = [3, 1, null, null, 2], k = 2
    Output: 2             (sorted values: 1, 2, 3)

Constraints:
    1 <= k <= n = number of nodes <= 10^4
    0 <= Node.val <= 10^4

Target: O(h + k) time (h = height of the tree), stopping as soon as the k-th
value is found.
Follow-up: if the tree were modified often (inserts and deletes) and asked for
the k-th smallest often, how would you make each query fast?
*/
#include "prelude.hpp"

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        throw NotImplemented();
    }
};
