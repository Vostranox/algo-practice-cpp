/*
54. Binary Tree Right Side View  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/binary-tree-right-side-view/

Picture yourself standing to the right of a binary tree. Return the values of
the nodes you can see, from top to bottom: for each level, the value of the
rightmost node on that level (which is not necessarily a right child). An empty
tree gives [].

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [7, 3, 9, 1, 5, null, null, null, null, 4]
    Output: [7, 9, 5, 4]  (4 is a left child, but nothing on its level is to its right)

Example 2:
    Input:  root = [2, null, 6, null, 8]
    Output: [2, 6, 8]

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
    vector<int> rightSideView(TreeNode* root) {
        throw NotImplemented();
    }
};
