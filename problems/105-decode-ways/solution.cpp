/*
105. Decode Ways  ·  Medium  ·  1-D Dynamic Programming
Source: https://leetcode.com/problems/decode-ways/

A message of capital letters was encoded with A -> "1", B -> "2", ..., Z -> "26"
and the codes were written one after another. Given the digit string `s`, count
the ways to cut it into consecutive pieces so that every piece is one of the 26
codes "1".."26". A piece with a leading zero is not a code: "0", "06" and "27"
are all invalid pieces. Return 0 if `s` can't be decoded at all.

Example 1:
    Input:  s = "1125"
    Output: 5          (1|1|2|5, 11|2|5, 1|12|5, 1|1|25, 11|25)

Example 2:
    Input:  s = "2101"
    Output: 1          (only 2|10|1; "01" and a lone "0" are not codes)

Example 3:
    Input:  s = "06"
    Output: 0

Constraints:
    1 <= s.length <= 100
    s consists of digits only and may start with '0'
    the answer fits in a 32-bit signed integer

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int numDecodings(string s) {
        throw NotImplemented();
    }
};
