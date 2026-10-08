/*
47. Maximum Depth of Binary Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/maximum-depth-of-binary-tree/

Return the maximum depth of a binary tree: the number of nodes on the longest
path from the root down to a leaf. An empty tree has depth 0, a lone root has
depth 1.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode* (nullptr for an empty tree). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [4, 2, 6, null, 3, 5]
    Output: 3             (4 -> 2 -> 3, or 4 -> 6 -> 5)

Example 2:
    Input:  root = [1, null, 2, null, 3, null, 4]
    Output: 4             (a chain of right children)

Example 3:
    Input:  root = []
    Output: 0

Constraints:
    0 <= number of nodes <= 10^4
    -100 <= Node.val <= 100

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxDepth(TreeNode* root) {
        throw NotImplemented();
    }
};
