/*
46. Invert Binary Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/invert-binary-tree/

Mirror a binary tree: at every node, swap its left and right child. Return the
root of the mirrored tree. You may rearrange the given nodes in place and
return the same root, or build a new tree.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [5, 3, 8, 1, 4, 7, 9]
    Output: [5, 8, 3, 9, 7, 4, 1]

Example 2:
    Input:  root = [2, 1, null, 0]
    Output: [2, null, 1, null, 0]
            (2 had only a left child 1, which had only a left child 0;
             after mirroring both are right children)

Example 3:
    Input:  root = []
    Output: []

Constraints:
    0 <= number of nodes <= 100
    -100 <= Node.val <= 100

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        throw NotImplemented();
    }
};
