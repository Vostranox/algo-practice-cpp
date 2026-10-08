/*
149. Sum of Two Integers  ·  Medium  ·  Bit Manipulation
Source: https://leetcode.com/problems/sum-of-two-integers/

Return a + b, computed without the + and - operators (so also no +=, -=, ++,
--, std::plus, accumulate, ...); use bit operations instead. Honor system: the
tests can't see how you did it.

Negative numbers are stored in two's complement, so the same bit trick works
for them as long as you stay within the fixed 32 bits of an int (that is the
part that needs masking in languages with unbounded integers, like Python).

Example 1:
    Input:  a = 3, b = 4
    Output: 7

Example 2:
    Input:  a = -6, b = 2
    Output: -4

Example 3:
    Input:  a = -5, b = -7
    Output: -12

Constraints:
    -1000 <= a, b <= 1000
*/
#include "prelude.hpp"

class Solution {
public:
    int getSum(int a, int b) {
        throw NotImplemented();
    }
};
