/*
108. Word Break  ·  Medium  ·  1-D Dynamic Programming
Source: https://leetcode.com/problems/word-break/

Return true if the string `s` can be cut into consecutive pieces so that every
piece is a word from `wordDict`, and false otherwise. A dictionary word may be
used any number of times, and not every word has to be used.

Example 1:
    Input:  s = "sunflower", wordDict = ["sun", "flower", "flow"]
    Output: true       ("sun" + "flower")

Example 2:
    Input:  s = "abab", wordDict = ["ab"]
    Output: true       (the same word twice)

Example 3:
    Input:  s = "carpet", wordDict = ["car", "pe", "pets"]
    Output: false      ("car" + "pe" leaves a "t" that is not a word)

Constraints:
    1 <= s.length <= 300
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 20
    s and every word consist of lowercase English letters
    the words in wordDict are distinct

Target: O(n * wordDict.length * L) time (L = max word length), O(n) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        throw NotImplemented();
    }
};
