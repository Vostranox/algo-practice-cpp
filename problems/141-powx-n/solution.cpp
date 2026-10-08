/*
141. Pow(x, n)  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/powx-n/

Compute x raised to the integer power n, i.e. x^n. n may be zero (x^0 = 1)
or negative (x^-k = 1 / x^k).

Implement it yourself with multiplications/divisions: don't call pow(),
std::pow, exp/log or similar shortcuts (honor system: the tests can't tell).
A result within 1e-5 of the exact value (absolute, or relative for large
values) is accepted.

Example 1:
    Input:  x = 3.0, n = 4
    Output: 81.0

Example 2:
    Input:  x = 1.5, n = 3
    Output: 3.375

Example 3:
    Input:  x = 2.0, n = -3
    Output: 0.125     (1 / 2^3)

Constraints:
    -100.0 < x < 100.0
    -2^31 <= n <= 2^31 - 1
    x != 0 or n > 0          (0 is never raised to a zero or negative power)
    -10^4 <= x^n <= 10^4

Target: O(log |n|) time. |n| can be about 2 * 10^9, so multiplying x into the
result |n| times is too slow. Careful: -n overflows an int when n = -2^31.
*/
#include "prelude.hpp"

class Solution {
public:
    double myPow(double x, int n) {
        throw NotImplemented();
    }
};
