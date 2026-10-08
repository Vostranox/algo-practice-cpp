/*
6. Product of Array Except Self  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/product-of-array-except-self/

You get an integer array `nums`. Return a new array `answer` of the same
length where answer[i] is the product of every element of `nums` except
nums[i].

Your solution must run in O(n) time and must NOT use the division operator.
(Products can be zero or negative; the inputs guarantee that the product of
any prefix or suffix of `nums` fits in a 32-bit signed integer.)

Example 1:
    Input:  nums = [2, 3, 4, 5]
    Output: [60, 40, 30, 24]

Example 2:
    Input:  nums = [-2, 0, 5, 3]
    Output: [0, -30, 0, 0]

Example 3:
    Input:  nums = [1, -1]
    Output: [-1, 1]

Constraints:
    2 <= nums.length <= 10^5
    -30 <= nums[i] <= 30
    every prefix/suffix product fits in a 32-bit signed integer

Target: O(n) time, no division.
Follow-up: use O(1) extra space besides the output array.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        throw NotImplemented();
    }
};
