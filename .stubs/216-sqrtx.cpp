/*
216. Sqrt(x)  ·  Easy  ·  Binary Search
Source: https://leetcode.com/problems/sqrtx/

You get a non-negative integer x. Return its square root rounded down to an
integer, i.e. the largest r with r * r <= x.

Compute it yourself: don't call sqrt(), pow(), exp/log or similar shortcuts
(honor system: the tests can't tell).

Example 1:
    Input:  x = 16
    Output: 4

Example 2:
    Input:  x = 27
    Output: 5             (the square root is 5.196..., rounded down)

Example 3:
    Input:  x = 0
    Output: 0

Constraints:
    0 <= x <= 2^31 - 1

Target: O(log x) time, e.g. binary search on r (Newton's method is faster
still). Trying r = 0, 1, 2, ... one by one takes up to 46341 steps per call,
which one test (3 * 10^5 calls with large x) doesn't allow. Careful: near
x = 2^31 - 1, both r * r and the sum of two ints can overflow an int.
*/
#include "prelude.hpp"

class Solution {
public:
    int mySqrt(int x) {
        throw NotImplemented();
    }
};
