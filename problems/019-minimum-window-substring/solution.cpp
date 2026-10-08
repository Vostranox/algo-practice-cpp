/*
19. Minimum Window Substring  ·  Hard  ·  Sliding Window
Source: https://leetcode.com/problems/minimum-window-substring/

You get two strings `s` and `t`. Return the shortest substring (contiguous
block) of `s` that contains every character of `t`, counting repeats: if `t`
has three 'a's, the window needs at least three 'a's. Other characters may
appear in the window too. Letters are case-sensitive ('a' != 'A').

If no such window exists, return the empty string "". The tests are built so
that the shortest window is unique.

Example 1:
    Input:  s = "xbyyaczabx", t = "abc"
    Output: "czab"

Example 2:
    Input:  s = "ayyaxa", t = "aa"
    Output: "axa"         (two a's needed; "ayya" is longer)

Example 3:
    Input:  s = "a", t = "aa"
    Output: ""

Constraints:
    1 <= s.length, t.length <= 10^5
    s and t consist of uppercase and lowercase English letters

Target: O(s.length + t.length) time.
*/
#include "prelude.hpp"

class Solution {
public:
    string minWindow(string s, string t) {
        throw NotImplemented();
    }
};
