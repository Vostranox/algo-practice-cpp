/*
161. Roman to Integer  ·  Easy  ·  Math & Geometry
Source: https://leetcode.com/problems/roman-to-integer/

Roman numerals are built from seven letters:

    I = 1    V = 5    X = 10    L = 50    C = 100    D = 500    M = 1000

Letters are normally written from the largest value to the smallest and simply
added up: "XXVII" = 10 + 10 + 5 + 1 + 1 = 27. Six two-letter combinations break
that order: a smaller letter written just before a larger one is subtracted
from it.

    IV = 4    IX = 9    XL = 40    XC = 90    CD = 400    CM = 900

Given a valid Roman numeral `s`, return the integer it stands for.

Example 1:
    Input:  s = "VIII"
    Output: 8         (5 + 1 + 1 + 1)

Example 2:
    Input:  s = "XLIX"
    Output: 49        (XL = 40, IX = 9)

Example 3:
    Input:  s = "MMCDXXI"
    Output: 2421      (MM = 2000, CD = 400, XX = 20, I = 1)

Constraints:
    1 <= s.length <= 15
    s contains only the letters I, V, X, L, C, D, M
    s is a valid numeral in the standard form, with a value between 1 and 3999

Target: O(s.length) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int romanToInt(string s) {
        throw NotImplemented();
    }
};
