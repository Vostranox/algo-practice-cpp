/*
56. Validate Binary Search Tree  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/validate-binary-search-tree/

Return true if the binary tree is a valid binary search tree, i.e. at every
node:
    - every value in its left subtree is strictly smaller than the node's value,
    - every value in its right subtree is strictly larger than the node's value.
(So equal values anywhere in the tree make it invalid.) Otherwise return false.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [8, 3, 10, 1, 6]
    Output: true

Example 2:
    Input:  root = [8, 3, 10, 1, 9]
    Output: false         (9 is a fine right child of 3, but it sits in the
                           left subtree of 8 and 9 > 8)

Example 3:
    Input:  root = [5, null, 5]
    Output: false         (equal values are not allowed)

Constraints:
    1 <= number of nodes <= 10^4
    -2^31 <= Node.val <= 2^31 - 1

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        throw NotImplemented();
    }
};
