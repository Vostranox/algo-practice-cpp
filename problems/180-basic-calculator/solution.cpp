/*
180. Basic Calculator  ·  Hard  ·  Stack
Source: https://leetcode.com/problems/basic-calculator/

You get a string `s` holding a valid arithmetic expression. Evaluate it and
return the result, without using any built-in expression evaluator.

The expression consists of non-negative integer literals, the operators '+'
and '-', parentheses '(' ')' and spaces (which can appear anywhere between the
other tokens and mean nothing). '+' and '-' are evaluated left to right, so
"10 - 2 - 3" is (10 - 2) - 3. Besides that, '-' may be used as a unary minus,
but only at the very start of the expression or right after a '(':
"-4 + 1" and "1 - (-2)" are valid. '+' is never unary, and two operators never
follow each other directly.

Every number, the final result and every intermediate result fit in a 32-bit
signed int.

Example 1:
    Input:  s = "7 - (2 + 3) + 1"
    Output: 3

Example 2:
    Input:  s = "-(4 - (1 + 9))"
    Output: 6             (-(4 - 10) = -(-6))

Example 3:
    Input:  s = " 12 "
    Output: 12

Constraints:
    1 <= s.length <= 3 * 10^5
    s consists of digits, '+', '-', '(', ')' and ' '
    s is a valid expression as described above

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int calculate(string s) {
        throw NotImplemented();
    }
};
