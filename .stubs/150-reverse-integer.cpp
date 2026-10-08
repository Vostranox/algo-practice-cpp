/*
150. Reverse Integer  ·  Medium  ·  Bit Manipulation
Source: https://leetcode.com/problems/reverse-integer/

Given a signed 32-bit integer x, return the number whose decimal digits are
those of x in reverse order, keeping the sign of x (zeros that end up in
front simply disappear: 120 -> 21). If the reversed value lies outside the
signed 32-bit range [-2^31, 2^31 - 1], return 0 instead.

Rule: pretend the machine cannot store 64-bit integers, so no int64_t
(honor system). Every intermediate value must fit in an int: detect the
overflow before it happens instead of building the full reversed number and
comparing afterwards. (Signed int overflow is undefined behaviour; the tests
run with UBSan, which reports it as a crash.)

Example 1:
    Input:  x = 4560
    Output: 654

Example 2:
    Input:  x = -317
    Output: -713

Example 3:
    Input:  x = 1000000009
    Output: 0         (9000000001 is larger than 2^31 - 1 = 2147483647)

Constraints:
    -2^31 <= x <= 2^31 - 1
*/
#include "prelude.hpp"

class Solution {
public:
    int reverse(int x) {
        throw NotImplemented();
    }
};
