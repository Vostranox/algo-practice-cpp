/*
51. Subtree of Another Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/subtree-of-another-tree/

Given two binary trees, root and subRoot, return true if some node of root,
taken together with ALL of its descendants, forms a tree identical to subRoot
(same shape, same values). Otherwise return false. The whole of root counts too.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the two root TreeNode pointers. TreeNode has int val and
TreeNode* left, right.

Example 1:
    Input:  root = [5, 3, 8, 1, 4], subRoot = [3, 1, 4]
    Output: true

Example 2:
    Input:  root = [5, 3, 8, 1, 4, null, null, null, null, 2], subRoot = [3, 1, 4]
    Output: false         (in root, node 4 has a child 2, so the subtree at 3 is
                           3 -> (1, 4 -> 2), which is not the same as subRoot)

Example 3:
    Input:  root = [1, 1], subRoot = [1]
    Output: true          (the leaf 1)

Constraints:
    1 <= number of nodes in root <= 2000
    1 <= number of nodes in subRoot <= 1000
    -10^4 <= Node.val <= 10^4

Target: O(m * n), comparing subRoot against every node, is fine here.
Follow-up: can you do it in O(m + n)?
*/
#include "prelude.hpp"

class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        throw NotImplemented();
    }
};
