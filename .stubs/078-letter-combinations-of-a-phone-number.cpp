/*
78. Letter Combinations of a Phone Number  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/letter-combinations-of-a-phone-number/

On a phone keypad the digits 2-9 carry these letters:
    2: abc   3: def   4: ghi   5: jkl   6: mno   7: pqrs   8: tuv   9: wxyz

Given a string `digits` made of the digits 2-9, return every string that can be
spelled by picking one letter for each digit, keeping the digits' order (the
i-th letter comes from the i-th digit). Return the strings in any order, each
exactly once. If digits is empty, return an empty list.

Example 1:
    Input:  digits = "47"
    Output: ["gp", "gq", "gr", "gs", "hp", "hq", "hr", "hs", "ip", "iq", "ir", "is"]

Example 2:
    Input:  digits = "9"
    Output: ["w", "x", "y", "z"]

Example 3:
    Input:  digits = ""
    Output: []

Constraints:
    0 <= digits.length <= 4
    each digits[i] is one of '2'-'9'

Target: O(n * 4^n) backtracking -- one recursion level per digit.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        throw NotImplemented();
    }
};
