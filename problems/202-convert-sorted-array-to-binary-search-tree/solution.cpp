/*
202. Convert Sorted Array to Binary Search Tree  ·  Easy  ·  Trees
Source: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

You get an integer array `nums` sorted in strictly increasing order. Build a
binary search tree (every value in a node's left subtree is smaller than the
node's value, every value in its right subtree is larger) that holds each
value of nums exactly once and is height-balanced: at every node, the heights
of the left and right subtrees differ by at most 1. Return its root.

Usually several trees qualify; any of them is accepted. The tests check the
properties above rather than one particular tree.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). Return a
TreeNode*; TreeNode has int val and TreeNode* left, right.

Example 1:
    Input:  nums = [-6, -2, 0, 5, 9]
    Output: [0, -2, 9, -6, null, 5]
            ([0, -6, 5, null, -2, null, 9] is just as good)

Example 2:
    Input:  nums = [1, 3]
    Output: [1, null, 3]    (or [3, 1])

Example 3:
    Input:  nums = [7]
    Output: [7]

Constraints:
    1 <= nums.length <= 10^4
    -10^4 <= nums[i] <= 10^4
    nums is strictly increasing

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        throw NotImplemented();
    }
};
