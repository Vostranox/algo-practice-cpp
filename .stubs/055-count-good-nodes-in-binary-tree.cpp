/*
55. Count Good Nodes in Binary Tree  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/count-good-nodes-in-binary-tree/

Call a node X "good" if no node on the path from the root down to X has a value
strictly greater than X's value (equal values are fine). The root is always
good. Return the number of good nodes in the tree.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [5, 2, 8, 6, 1, 7, 9]
    Output: 4             (5, 8, 9, and 6 on the path 5 -> 2 -> 6; 2, 1 and 7
                           each have a larger value above them)

Example 2:
    Input:  root = [4, 4, null, 4, 3]
    Output: 3             (the three 4s; 3 is below a 4)

Example 3:
    Input:  root = [-7]
    Output: 1

Constraints:
    1 <= number of nodes <= 10^5
    -10^4 <= Node.val <= 10^4

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int goodNodes(TreeNode* root) {
        throw NotImplemented();
    }
};
