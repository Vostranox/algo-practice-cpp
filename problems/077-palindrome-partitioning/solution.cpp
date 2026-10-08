/*
77. Palindrome Partitioning  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/palindrome-partitioning/

Given a string s, cut it into consecutive non-empty pieces so that every piece
is a palindrome (reads the same forwards and backwards). Return every way of
doing this. Each way is the list of its pieces in their original order (so
joining them gives back s). Return the ways in any order, each exactly once.

Example 1:
    Input:  s = "abb"
    Output: [["a", "b", "b"], ["a", "bb"]]

Example 2:
    Input:  s = "noon"
    Output: [["n", "o", "o", "n"], ["n", "oo", "n"], ["noon"]]

Example 3:
    Input:  s = "z"
    Output: [["z"]]

Constraints:
    1 <= s.length <= 16
    s consists of lowercase English letters

Target: O(n * 2^n) backtracking -- choose the first piece (it must be a
palindrome), then partition the rest of the string the same way.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<string>> partition(string s) {
        throw NotImplemented();
    }
};
