/*
174. Isomorphic Strings  ·  Easy  ·  Arrays & Hashing
Source: https://leetcode.com/problems/isomorphic-strings/

Two strings `s` and `t` of the same length are isomorphic if `t` can be
obtained from `s` by a character substitution: every occurrence of a
character in `s` is replaced by the same character, and two different
characters of `s` never get the same replacement. (A character may stay as it
is.) Return true if `s` and `t` are isomorphic, otherwise false.

Example 1:
    Input:  s = "abca", t = "zyxz"
    Output: true          (a -> z, b -> y, c -> x)

Example 2:
    Input:  s = "aab", t = "xyz"
    Output: false         (a would have to become both x and y)

Example 3:
    Input:  s = "ab", t = "cc"
    Output: false         (a and b can't both become c)

Constraints:
    1 <= s.length <= 5 * 10^4
    t.length == s.length
    s and t consist of ASCII characters (letters, digits, spaces, symbols, ...)

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        throw NotImplemented();
    }
};
