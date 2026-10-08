/*
190. Sum Root to Leaf Numbers  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/sum-root-to-leaf-numbers/

Every node of a binary tree holds a single digit 0-9. Reading the digits along
a path from the root down to a leaf (a node without children) gives a number,
with the root's digit as the most significant one; leading zeros are allowed
(the path 0 -> 5 reads 5). Return the sum of the numbers of all root-to-leaf
paths.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [2, 7, 5, null, 3]
    Output: 298           (273 + 25)

Example 2:
    Input:  root = [0, 1, 6]
    Output: 7             (01 + 06)

Example 3:
    Input:  root = [1, 2, null, 3]
    Output: 123           (one path; 1 and 12 end at inner nodes and don't count)

Constraints:
    1 <= number of nodes <= 1000
    0 <= Node.val <= 9
    the depth of the tree is at most 10
    the answer fits in a 32-bit signed int

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        throw NotImplemented();
    }
};
