/*
112. Longest Common Subsequence  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/longest-common-subsequence/

A subsequence of a string is what remains after deleting any number of its
characters (possibly none) without changing the order of the rest. Return the
length of the longest string that is a subsequence of both `text1` and `text2`,
or 0 if they have no character in common.

Example 1:
    Input:  text1 = "stone", text2 = "longest"
    Output: 3          ("one")

Example 2:
    Input:  text1 = "abc", text2 = "abc"
    Output: 3

Example 3:
    Input:  text1 = "abc", text2 = "xyz"
    Output: 0

Constraints:
    1 <= text1.length, text2.length <= 1000
    both strings consist of lowercase English letters

Target: O(text1.length * text2.length) time, O(min(text1.length, text2.length)) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        throw NotImplemented();
    }
};
