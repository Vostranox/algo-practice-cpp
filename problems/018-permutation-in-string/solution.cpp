/*
18. Permutation in String  ·  Medium  ·  Sliding Window
Source: https://leetcode.com/problems/permutation-in-string/

You get two strings `s1` and `s2`. Return true if some contiguous substring of
`s2` is a permutation of `s1`, i.e. has exactly the same letters with exactly
the same counts as `s1` (so it is s1.length characters long). Otherwise return
false.

Example 1:
    Input:  s1 = "abc", s2 = "lecabee"
    Output: true          (s2 contains "cab")

Example 2:
    Input:  s1 = "abc", s2 = "lecaabee"
    Output: false         (no 3-letter window holds exactly one a, b and c)

Example 3:
    Input:  s1 = "abcd", s2 = "dcb"
    Output: false         (s2 is shorter than s1)

Constraints:
    1 <= s1.length, s2.length <= 10^4
    s1 and s2 consist of lowercase English letters

Target: O(s1.length + s2.length) time (a factor of 26 is fine).
*/
#include "prelude.hpp"

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        throw NotImplemented();
    }
};
