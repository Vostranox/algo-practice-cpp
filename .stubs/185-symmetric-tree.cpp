/*
185. Symmetric Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/symmetric-tree/

Return true if a binary tree is its own mirror image around a vertical line
through the root: flipping the whole tree left-to-right (swapping the children
of every node) gives back the same shape with the same values in the same
places. Otherwise return false.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [4, 7, 7, 1, 9, 9, 1]
    Output: true

Example 2:
    Input:  root = [4, 7, 7, null, 9, null, 9]
    Output: false         (both 9s are right children; in a mirror image one of
                           them would have to be a left child)

Example 3:
    Input:  root = [1, 2, 2, 2, null, 2]
    Output: false         (the inorder sequence 2, 2, 1, 2, 2 reads the same
                           backwards, but the shapes don't mirror each other)

Constraints:
    1 <= number of nodes <= 1000
    -100 <= Node.val <= 100

Target: O(n) time.
Follow-up: can you solve it both recursively and iteratively?
*/
#include "prelude.hpp"

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        throw NotImplemented();
    }
};
