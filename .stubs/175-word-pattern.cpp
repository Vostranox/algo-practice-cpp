/*
175. Word Pattern  ·  Easy  ·  Arrays & Hashing
Source: https://leetcode.com/problems/word-pattern/

You get a `pattern` of letters and a string `s` of words separated by single
spaces. `s` follows the pattern if the letters and the words can be paired up
one-to-one: s has exactly one word per letter of the pattern, equal letters
always stand for equal words, and different letters always stand for
different words. Return true if `s` follows `pattern`, otherwise false.

Example 1:
    Input:  pattern = "xyyx", s = "red blue blue red"
    Output: true

Example 2:
    Input:  pattern = "xyyx", s = "red blue blue blue"
    Output: false         (x stands for both red and blue)

Example 3:
    Input:  pattern = "xy", s = "sun sun"
    Output: false         (x and y can't both stand for sun)

Constraints:
    1 <= pattern.length <= 300
    pattern consists of lowercase English letters
    1 <= s.length <= 3000
    s consists of lowercase English letters and spaces; it has no leading or
    trailing spaces, and its words are separated by single spaces

Target: O(n + m) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        throw NotImplemented();
    }
};
