/*
192. Count Complete Tree Nodes  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/count-complete-tree-nodes/

You get the root of a complete binary tree: every level is completely filled
except possibly the last one, whose nodes are packed as far left as possible.
Return the number of nodes in the tree.

Counting by visiting every node is easy; the point of the problem is to do it
faster than that, using the shape guarantee.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [9, 4, 7, 1, 3, 8, 2, 5]
    Output: 8

Example 2:
    Input:  root = [6, 6, 6]
    Output: 3

Example 3:
    Input:  root = []
    Output: 0

Constraints:
    0 <= number of nodes <= 5 * 10^4
    0 <= Node.val <= 5 * 10^4
    the tree is complete

Target: less than O(n) time per call, e.g. O(log^2 n); the tests call
countNodes 10^5 times on trees with tens of thousands of nodes, so visiting
every node is too slow.
*/
#include "prelude.hpp"

class Solution {
public:
    int countNodes(TreeNode* root) {
        throw NotImplemented();
    }
};
