/*
142. Multiply Strings  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/multiply-strings/

Two non-negative integers are given as decimal strings `num1` and `num2`.
Return their product, also as a decimal string, without leading zeros (a zero
product is "0").

The numbers can have 200 digits, far more than any built-in integer type
holds, so converting the strings with stoi/stoll/stoull doesn't work: do the
arithmetic digit by digit, like long multiplication on paper.

Example 1:
    Input:  num1 = "12", num2 = "12"
    Output: "144"

Example 2:
    Input:  num1 = "123", num2 = "45"
    Output: "5535"

Example 3:
    Input:  num1 = "0", num2 = "987"
    Output: "0"

Constraints:
    1 <= num1.length, num2.length <= 200
    num1 and num2 contain only the digits 0-9
    no leading zeros, except for the number 0 itself ("0")

Target: O(num1.length * num2.length) time.
*/
#include "prelude.hpp"

class Solution {
public:
    string multiply(string num1, string num2) {
        throw NotImplemented();
    }
};
