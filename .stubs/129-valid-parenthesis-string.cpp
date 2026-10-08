/*
129. Valid Parenthesis String  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/valid-parenthesis-string/

The string `s` contains only the characters '(', ')' and '*'. Every '*' is a
wildcard: you may independently turn each one into '(', into ')', or delete
it. Return true if some choice of wildcards turns `s` into a balanced string,
otherwise false.

Balanced means: every '(' is closed by a later ')', and every ')' closes an
earlier '('. (The empty string is balanced.)

Example 1:
    Input:  s = "(*()"
    Output: true          (use the '*' as ')' to get "()()")

Example 2:
    Input:  s = "*)("
    Output: false         (nothing after the last '(' can close it)

Example 3:
    Input:  s = "**())"
    Output: true          (first '*' -> '(', second deleted: "(())")

Constraints:
    1 <= s.length <= 100
    s[i] is '(', ')' or '*'

Target: O(n) time, O(1) extra space. (An O(n^2) DP also fits these limits;
trying every wildcard choice does not.)
*/
#include "prelude.hpp"

class Solution {
public:
    bool checkValidString(string s) {
        throw NotImplemented();
    }
};
