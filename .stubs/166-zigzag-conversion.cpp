/*
166. Zigzag Conversion  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/zigzag-conversion/

Write the characters of `s`, in order, along a zigzag over `numRows` rows:
go straight down from row 0 to row numRows - 1, then diagonally back up to
row 0, then down again, and so on. Then read the rows from top to bottom,
each one from left to right, and return the resulting string.

Example 1:
    Input:  s = "ABCDEFGHIJ", numRows = 3
    Output: "AEIBDFHJCG"
            A   E   I
            B D F H J
            C   G

Example 2:
    Input:  s = "ABCDEFGHIJ", numRows = 4
    Output: "AGBFHCEIDJ"
            A     G
            B   F H
            C E   I
            D     J

Example 3:
    Input:  s = "hello", numRows = 1
    Output: "hello"

Constraints:
    1 <= s.length <= 1000
    s consists of English letters (upper and lower case), ',' and '.'
    1 <= numRows <= 1000

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    string convert(string s, int numRows) {
        throw NotImplemented();
    }
};
