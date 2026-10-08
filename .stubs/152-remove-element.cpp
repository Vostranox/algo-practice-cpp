/*
152. Remove Element  ·  Easy  ·  Arrays & Hashing
Source: https://leetcode.com/problems/remove-element/

You get an integer array `nums` and an integer `val`. Remove every occurrence
of `val` from `nums` in place: if k values of `nums` differ from `val`, move
exactly those k values (in any order) into the first k positions of `nums`,
and return k. What is left in the positions from k onwards doesn't matter.

Example 1:
    Input:  nums = [4, 1, 4, 2], val = 4
    Output: 2             (nums starts with 1, 2 in some order, e.g. [1, 2, _, _])

Example 2:
    Input:  nums = [0, 5, 5, 3, 5, 0, 7], val = 5
    Output: 4             (the first 4 positions hold 0, 0, 3, 7 in any order)

Example 3:
    Input:  nums = [6, 6], val = 6
    Output: 0

Constraints:
    0 <= nums.length <= 100
    0 <= nums[i] <= 50
    0 <= val <= 100

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        throw NotImplemented();
    }
};
