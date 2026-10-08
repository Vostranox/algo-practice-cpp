/*
188. Flatten Binary Tree to Linked List  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

Rearrange a binary tree, in place, into a "linked list" made of its own
nodes: the nodes in preorder (a node, then its left subtree, then its right
subtree), each one pointing to the next through its right pointer, with every
left pointer set to nullptr. Don't create new nodes. The function returns
nothing; the list starts at the original root.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [5, 3, 8, 1, 4, null, 9]
    Output: [5, null, 3, null, 1, null, 4, null, 8, null, 9]
            (preorder: 5, 3, 1, 4, 8, 9)

Example 2:
    Input:  root = [1, null, 2, 3]
    Output: [1, null, 2, null, 3]

Example 3:
    Input:  root = []
    Output: []

Constraints:
    0 <= number of nodes <= 2000
    -100 <= Node.val <= 100

Target: O(n) time.
Follow-up: can you do it with O(1) extra space (no recursion, no stack)?
*/
#include "prelude.hpp"

class Solution {
public:
    void flatten(TreeNode* root) {
        throw NotImplemented();
    }
};
