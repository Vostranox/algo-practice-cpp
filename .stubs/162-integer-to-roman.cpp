/*
162. Integer to Roman  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/integer-to-roman/

Roman numerals are built from seven letters:

    I = 1    V = 5    X = 10    L = 50    C = 100    D = 500    M = 1000

Given an integer `num`, return its standard Roman numeral. The standard form
writes the decimal digits from the thousands down to the ones, each digit
on its own, using the letters of its place: (I, V, X) for ones, (X, L, C) for
tens, (C, D, M) for hundreds and M for thousands. With "one", "five" and "ten"
standing for those three letters, a digit d becomes

    d = 0      nothing
    d = 1..3   "one" repeated d times               (I, II, III)
    d = 4      "one" then "five"                    (IV)
    d = 5..8   "five" followed by d - 5 "one"s      (V, VI, VII, VIII)
    d = 9      "one" then "ten"                     (IX)

So subtraction is only ever IV, IX, XL, XC, CD and CM: 49 is "XLIX", never
"IL", and no letter appears more than three times in a row.

Example 1:
    Input:  num = 68
    Output: "LXVIII"      (60 = LX, 8 = VIII)

Example 2:
    Input:  num = 49
    Output: "XLIX"        (40 = XL, 9 = IX)

Example 3:
    Input:  num = 2894
    Output: "MMDCCCXCIV"  (2000 = MM, 800 = DCCC, 90 = XC, 4 = IV)

Constraints:
    1 <= num <= 3999
*/
#include "prelude.hpp"

class Solution {
public:
    string intToRoman(int num) {
        throw NotImplemented();
    }
};
