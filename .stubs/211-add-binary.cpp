/*
211. Add Binary  ·  Easy  ·  Bit Manipulation
Source: https://leetcode.com/problems/add-binary/

Two non-negative integers are given as binary strings `a` and `b` (made of
the characters '0' and '1', most significant bit first). Return their sum,
also as a binary string without leading zeros (a zero sum is "0").

The strings can be 10^4 bits long, far more than any built-in integer type
holds, so add them bit by bit with a carry, like column addition on paper.

Example 1:
    Input:  a = "101", b = "11"
    Output: "1000"      (5 + 3 = 8)

Example 2:
    Input:  a = "1101", b = "1011"
    Output: "11000"     (13 + 11 = 24)

Example 3:
    Input:  a = "0", b = "110"
    Output: "110"

Constraints:
    1 <= a.length, b.length <= 10^4
    a and b contain only the characters '0' and '1'
    no leading zeros, except for the number 0 itself ("0")

Target: O(max(a.length, b.length)) time.
*/
#include "prelude.hpp"

class Solution {
public:
    string addBinary(string a, string b) {
        throw NotImplemented();
    }
};
