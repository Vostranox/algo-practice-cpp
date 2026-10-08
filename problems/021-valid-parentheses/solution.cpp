/*
21. Valid Parentheses  ·  Easy  ·  Stack
Source: https://leetcode.com/problems/valid-parentheses/

You get a string `s` made only of the bracket characters ( ) [ ] { }.
Return true if its brackets are properly matched, otherwise false. They are
properly matched when:
    - every opening bracket is closed by a closing bracket of the same kind,
    - brackets are closed in the reverse order they were opened (a pair that
      starts inside another pair must also end inside it), and
    - every closing bracket has an unmatched opening bracket before it.

Example 1:
    Input:  s = "{[()()]}"
    Output: true

Example 2:
    Input:  s = "([)]"
    Output: false         (the "[" would be closed by ")" - the pairs cross)

Example 3:
    Input:  s = "(()"
    Output: false         (one "(" is never closed)

Constraints:
    1 <= s.length <= 10^4
    s contains only the characters ()[]{}

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isValid(string s) {
        throw NotImplemented();
    }
};
