/*
118. Distinct Subsequences  ·  Hard  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/distinct-subsequences/

Count the ways to obtain `t` by deleting characters from `s`: that is, the
number of different sets of positions i1 < i2 < ... < ik in s (k = t.length)
with s[i1] s[i2] ... s[ik] == t. Two ways count as different when they use a
different set of positions, even if they look alike. Letters are case-sensitive.

Example 1:
    Input:  s = "bagbag", t = "bag"
    Output: 4          (positions 0-1-2, 0-1-5, 0-4-5, 3-4-5)

Example 2:
    Input:  s = "aaa", t = "aa"
    Output: 3

Example 3:
    Input:  s = "abc", t = "abd"
    Output: 0

Constraints:
    1 <= s.length, t.length <= 1000
    s and t consist of English letters (upper and lower case)
    the answer fits in a 32-bit signed integer (counts for parts of the strings
    may be far larger, so watch out for overflow in intermediate values)

Target: O(s.length * t.length) time, O(t.length) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int numDistinct(string s, string t) {
        throw NotImplemented();
    }
};
