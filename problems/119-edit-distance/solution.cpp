/*
119. Edit Distance  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/edit-distance/

Return the minimum number of single-character edits that turn `word1` into
`word2`, where an edit is one of:
  - insert a character anywhere,
  - delete a character,
  - replace a character by another one.

Example 1:
    Input:  word1 = "kitten", word2 = "sitting"
    Output: 3          (k -> s, e -> i, insert g at the end)

Example 2:
    Input:  word1 = "flaw", word2 = "lawn"
    Output: 2          (delete f, insert n at the end)

Example 3:
    Input:  word1 = "", word2 = "abc"
    Output: 3

Constraints:
    0 <= word1.length, word2.length <= 500
    word1 and word2 consist of lowercase English letters

Target: O(word1.length * word2.length) time, O(min(word1.length, word2.length)) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int minDistance(string word1, string word2) {
        throw NotImplemented();
    }
};
