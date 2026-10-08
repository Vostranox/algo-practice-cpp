/*
196. Minimum Absolute Difference in BST  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/minimum-absolute-difference-in-bst/

You get the root of a binary search tree (every value in a node's left subtree
is smaller than the node's value, every value in its right subtree is larger,
so all values are distinct). Return the smallest absolute difference between
the values of two different nodes of the tree, which need not be parent and
child.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [50, 20, 80, null, 48]
    Output: 2             (48 and 50; 48 is a grandchild of 50)

Example 2:
    Input:  root = [6, 2, 9, 1, 4]
    Output: 1             (1 and 2)

Example 3:
    Input:  root = [0, null, 100000]
    Output: 100000

Constraints:
    2 <= number of nodes <= 10^4
    0 <= Node.val <= 10^5

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        throw NotImplemented();
    }
};
