/*
194. Average of Levels in Binary Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/average-of-levels-in-binary-tree/

Return the average of the values on each level of a binary tree, as one
number per level, from the root level downwards. Answers within 10^-5 of the
exact averages are accepted.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Your function
receives the root TreeNode*. TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  root = [4, 2, 9, null, null, 5, 8]
    Output: [4, 5.5, 6.5]       (levels [4], [2, 9], [5, 8])

Example 2:
    Input:  root = [-3, 10, -7, 1]
    Output: [-3, 1.5, 1]

Example 3:
    Input:  root = [2147483647, 2147483647, 2147483647]
    Output: [2147483647, 2147483647]
            (the two values on level 2 add up to more than an int can hold)

Constraints:
    1 <= number of nodes <= 10^4
    -2^31 <= Node.val <= 2^31 - 1

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        throw NotImplemented();
    }
};
