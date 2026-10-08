/*
23. Evaluate Reverse Polish Notation  ·  Medium  ·  Stack
Source: https://leetcode.com/problems/evaluate-reverse-polish-notation/

An arithmetic expression is given in Reverse Polish (postfix) notation as a
list of string tokens, where every operator comes right after its two operands.
Evaluate it and return the resulting integer.

Each token is either an integer (possibly negative, e.g. "-12") or one of the
operators "+", "-", "*", "/". An operator combines the two most recent values,
a (the earlier one) and b (the later one), into a + b, a - b, a * b or a / b.

Division is integer division that truncates toward zero:
    7 / 2 = 3,   -7 / 2 = -3,   7 / -2 = -3,   -1 / 3 = 0
(which is exactly what C++'s int division does).

The expression is always valid, never divides by zero, and the result as well
as every intermediate value fits in a 32-bit signed int.

Example 1:
    Input:  tokens = ["3", "4", "+", "5", "*"]
    Output: 35            ((3 + 4) * 5)

Example 2:
    Input:  tokens = ["20", "6", "-7", "+", "/"]
    Output: -20           (20 / (6 + -7))

Example 3:
    Input:  tokens = ["-9", "4", "/", "6", "2", "-", "*"]
    Output: -8            (-9 / 4 truncates to -2, then -2 * (6 - 2))

Constraints:
    1 <= tokens.length <= 10^4
    each token is "+", "-", "*", "/" or an integer in the range [-200, 200]

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        throw NotImplemented();
    }
};
