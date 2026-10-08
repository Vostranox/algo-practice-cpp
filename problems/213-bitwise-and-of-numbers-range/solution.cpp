/*
213. Bitwise AND of Numbers Range  ·  Medium  ·  Bit Manipulation
Source: https://leetcode.com/problems/bitwise-and-of-numbers-range/

Given two integers left <= right, return the bitwise AND of every integer in
the range [left, right], both ends included:
left & (left + 1) & ... & right.

Example 1:
    Input:  left = 12, right = 15
    Output: 12    (1100 & 1101 & 1110 & 1111 = 1100)

Example 2:
    Input:  left = 26, right = 30
    Output: 24    (11010 & 11011 & 11100 & 11101 & 11110 = 11000)

Example 3:
    Input:  left = 9, right = 9
    Output: 9

Constraints:
    0 <= left <= right <= 2^31 - 1

Target: O(log right) time. The range can hold more than two billion numbers,
so AND-ing them one by one is too slow.
*/
#include "prelude.hpp"

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        throw NotImplemented();
    }
};
