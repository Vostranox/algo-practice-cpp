/*
116. Interleaving String  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/interleaving-string/

Return true if `s3` can be formed by merging `s1` and `s2`: every character of
s1 and of s2 is used exactly once, and the characters of s1 appear in s3 in
their original order, as do the characters of s2 (like shuffling two decks of
cards together). Otherwise return false. In particular s3 must have exactly
s1.length + s2.length characters.

Example 1:
    Input:  s1 = "abc", s2 = "xy", s3 = "axbyc"
    Output: true

Example 2:
    Input:  s1 = "ab", s2 = "cd", s3 = "adcb"
    Output: false      (s2's "d" can't come before its "c")

Example 3:
    Input:  s1 = "aa", s2 = "ab", s3 = "abaa"
    Output: true       ("ab" from s2, then "aa" from s1)

Constraints:
    0 <= s1.length, s2.length <= 100
    0 <= s3.length <= 200
    s1, s2 and s3 consist of lowercase English letters

Target: O(s1.length * s2.length) time.
Follow-up: O(s2.length) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        throw NotImplemented();
    }
};
