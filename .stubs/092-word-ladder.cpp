/*
92. Word Ladder  ·  Hard  ·  Graphs
Source: https://leetcode.com/problems/word-ladder/

A ladder from `beginWord` to `endWord` is a sequence of words
beginWord = w0, w1, ..., wk = endWord in which every two consecutive words
differ in exactly one letter (same length, one position changed), and every
word after w0 is taken from `wordList` (beginWord itself does not have to be in
the list). Return the number of words in the shortest such ladder (counting
both beginWord and endWord), or 0 if no ladder exists.

Example 1:
    Input:  beginWord = "cold", endWord = "warm",
            wordList = ["cord", "card", "ward", "warm", "worm", "word", "wold"]
    Output: 5       (cold -> cord -> card -> ward -> warm; all 4 letters must change)

Example 2:
    Input:  beginWord = "lead", endWord = "gold", wordList = ["load", "goad", "gold"]
    Output: 4       (lead -> load -> goad -> gold)

Example 3:
    Input:  beginWord = "lead", endWord = "gold", wordList = ["load", "goad"]
    Output: 0       (endWord is not in the list)

Constraints:
    1 <= beginWord.length <= 10,  endWord.length == beginWord.length
    1 <= wordList.length <= 5000,  wordList[i].length == beginWord.length
    all words consist of lowercase English letters
    beginWord != endWord; the words in wordList are distinct

Target: O(N * L^2) time with N = wordList.length, L = word length
        (e.g. BFS that finds neighbours via wildcard patterns or letter substitution).
*/
#include "prelude.hpp"

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        throw NotImplemented();
    }
};
