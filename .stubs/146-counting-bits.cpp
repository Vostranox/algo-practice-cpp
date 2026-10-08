/*
146. Counting Bits  ·  Easy  ·  Bit Manipulation
Source: https://leetcode.com/problems/counting-bits/

Given an integer n >= 0, return an array `ans` of length n + 1 where ans[i] is
the number of 1 bits in the binary representation of i, for every i from 0
to n.

Example 1:
    Input:  n = 3
    Output: [0, 1, 1, 2]           (0, 1, 10, 11)

Example 2:
    Input:  n = 6
    Output: [0, 1, 1, 2, 1, 2, 2]  (..., 100, 101, 110)

Example 3:
    Input:  n = 0
    Output: [0]

Constraints:
    0 <= n <= 10^5

Follow-up: counting the bits of each number separately takes O(n log n). Can
you do it in O(n) with a single pass, reusing earlier answers, and without
built-ins such as __builtin_popcount?
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> countBits(int n) {
        throw NotImplemented();
    }
};
