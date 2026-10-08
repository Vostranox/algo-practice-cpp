/*
17. Longest Repeating Character Replacement  ·  Medium  ·  Sliding Window
Source: https://leetcode.com/problems/longest-repeating-character-replacement/

You get a string `s` of uppercase English letters and an integer `k`. You may
pick at most `k` positions of `s` and overwrite each with any uppercase letter.
Return the length of the longest substring consisting of one repeated letter
that you can obtain this way.

Example 1:
    Input:  s = "XYYX", k = 2
    Output: 4             (overwrite both X's with Y: "YYYY")

Example 2:
    Input:  s = "AAABABB", k = 1
    Output: 5             ("AAABA" -> "AAAAA")

Example 3:
    Input:  s = "BAAAB", k = 0
    Output: 3             (no changes allowed: "AAA")

Constraints:
    1 <= s.length <= 10^5
    s consists of uppercase English letters
    0 <= k <= s.length

Target: O(n) time (O(26 * n) is fine).
*/
#include "prelude.hpp"

class Solution {
public:
    int characterReplacement(string s, int k) {
        throw NotImplemented();
    }
};
