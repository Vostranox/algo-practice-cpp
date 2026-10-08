/*
50. Same Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/same-tree/

Given the roots of two binary trees p and q, return true if they are identical:
the same shape, with equal values in corresponding nodes. Otherwise return
false. Two empty trees are identical.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives root TreeNode pointers (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  p = [4, 7, 9], q = [4, 7, 9]
    Output: true

Example 2:
    Input:  p = [4, 7], q = [4, null, 7]
    Output: false         (same values, but 7 is a left child in p and a right child in q)

Example 3:
    Input:  p = [2, 1, 3], q = [2, 3, 1]
    Output: false

Constraints:
    0 <= number of nodes in each tree <= 100
    -10^4 <= Node.val <= 10^4

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        throw NotImplemented();
    }
};
