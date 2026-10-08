/*
10. Valid Palindrome  ·  Easy  ·  Two Pointers
Source: https://leetcode.com/problems/valid-palindrome/

You get a string `s`. Lowercase every uppercase letter and throw away every
character that is not a letter or a digit (spaces, punctuation, '_', ...).
Return true if what remains reads the same forwards and backwards, otherwise
false. If nothing remains, the (empty) result counts as a palindrome.

Example 1:
    Input:  s = "Was it a car, or a cat I saw?"
    Output: true          ("wasitacaroracatisaw")

Example 2:
    Input:  s = "ab2a"
    Output: false         (digits are kept: "ab2a" reversed is "a2ba")

Example 3:
    Input:  s = " .,! "
    Output: true          (nothing is left)

Constraints:
    1 <= s.length <= 2 * 10^5
    s consists only of printable ASCII characters

Target: O(n) time; O(1) extra space with two pointers.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isPalindrome(string s) {
        throw NotImplemented();
    }
};
