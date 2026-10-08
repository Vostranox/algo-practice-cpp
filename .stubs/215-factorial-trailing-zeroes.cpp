/*
215. Factorial Trailing Zeroes  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/factorial-trailing-zeroes/

Given an integer n, return how many zeros the decimal representation of
n! = 1 * 2 * ... * n ends with. By definition 0! = 1.

n! grows enormously fast: 21! already doesn't fit in 64 bits and 10000! has
more than 35000 digits, so computing the factorial itself is not the way.

Example 1:
    Input:  n = 4
    Output: 0     (4! = 24)

Example 2:
    Input:  n = 10
    Output: 2     (10! = 3628800)

Example 3:
    Input:  n = 25
    Output: 6     (25! = 15511210043330985984000000)

Constraints:
    0 <= n <= 10^4

Follow-up: can you do it in O(log n) time? (honor system: with n <= 10^4 the
tests can't tell.)
*/
#include "prelude.hpp"

class Solution {
public:
    int trailingZeroes(int n) {
        throw NotImplemented();
    }
};
