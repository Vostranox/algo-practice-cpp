/*
189. Path Sum  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/path-sum/

You get a binary tree and an integer targetSum. Return true if some path
from the root down to a leaf (a node without children) has node values that
add up to exactly targetSum, and false otherwise. The path must end at a
leaf: stopping at a node that still has a child doesn't count. An empty tree
has no paths at all.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [3, 9, -2, null, null, 6, 1], targetSum = 7
    Output: true          (3 + -2 + 6; the other paths give 12 and 2)

Example 2:
    Input:  root = [3, 9, -2, null, null, 6, 1], targetSum = 1
    Output: false         (3 + -2 = 1, but -2 is not a leaf)

Example 3:
    Input:  root = [], targetSum = 0
    Output: false

Constraints:
    0 <= number of nodes <= 5000
    -1000 <= Node.val <= 1000
    -1000 <= targetSum <= 1000

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        throw NotImplemented();
    }
};
