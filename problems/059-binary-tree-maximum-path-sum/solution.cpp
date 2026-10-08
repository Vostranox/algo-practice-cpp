/*
59. Binary Tree Maximum Path Sum  ·  Hard  ·  Trees
Source: https://leetcode.com/problems/binary-tree-maximum-path-sum/

A path in a binary tree is a sequence of nodes in which each pair of
consecutive nodes is joined by an edge (parent-child), and no node appears
more than once. It contains at least one node, and it does not have to pass
through the root. Its sum is the sum of its nodes' values.

Return the largest sum of any path in the tree.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [1, -2, 3]
    Output: 4             (1 -> 3)

Example 2:
    Input:  root = [-5, 4, 8, null, null, 6, -1]
    Output: 14            (6 -> 8; going on through -5 to 4 would lower the sum)

Example 3:
    Input:  root = [-4, -2, -9]
    Output: -2            (every value is negative: the best path is the single node -2)

Constraints:
    1 <= number of nodes <= 3 * 10^4
    -1000 <= Node.val <= 1000

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        throw NotImplemented();
    }
};
