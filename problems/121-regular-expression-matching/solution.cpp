/*
121. Regular Expression Matching  ·  Hard  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/regular-expression-matching/

Decide whether the pattern `p` matches the WHOLE string `s` (not just a part of
it). Besides ordinary letters, which match themselves, the pattern may contain:
  '.'  matches any single character;
  '*'  matches zero or more repetitions of the element right before it
       (a letter or '.'), so "a*" matches "", "a", "aa", ... and ".*" matches
       any string.
Return true if p matches all of s, false otherwise.

Example 1:
    Input:  s = "abbbc", p = "ab*c"
    Output: true

Example 2:
    Input:  s = "abcd", p = "a.c"
    Output: false      ("a.c" matches "abc", but the "d" is left over)

Example 3:
    Input:  s = "zq", p = ".*"
    Output: true

Constraints:
    1 <= s.length <= 20
    1 <= p.length <= 20
    s consists of lowercase English letters
    p consists of lowercase English letters, '.' and '*'
    every '*' directly follows a letter or '.'

Target: O(s.length * p.length) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isMatch(string s, string p) {
        throw NotImplemented();
    }
};
