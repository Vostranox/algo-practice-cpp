/*
63. Word Search II  ·  Hard  ·  Tries
Source: https://leetcode.com/problems/word-search-ii/

You get an m x n grid `board` of lowercase letters and a list of distinct
lowercase `words`. Return every word from the list that can be traced on the
board, in any order, each word once.

A word is traced by starting at any cell and repeatedly stepping to a
horizontally or vertically adjacent cell, so that the letters of the visited
cells, in order, spell the word. Within one word a cell may be used at most
once (different words may of course reuse cells).

Example 1:
    Input:  board = [['c', 'a', 't'],
                     ['r', 'o', 'e'],
                     ['d', 'g', 's']]
            words = ["cat", "goes", "roe", "dog", "toe", "cart", "sea"]
    Output: ["cat", "goes", "roe"]       (any order)

Example 2:
    Input:  board = [['a', 'b'],
                     ['c', 'd']]
            words = ["abdc", "abcd", "acdb"]
    Output: ["abdc", "acdb"]             (b and c are not adjacent: no diagonal steps)

Example 3:
    Input:  board = [['x', 'y', 'x']], words = ["xyx", "xyxy"]
    Output: ["xyx"]                      ("xyxy" would need a cell twice)

Constraints:
    1 <= m, n <= 12
    1 <= words.length <= 3 * 10^4
    1 <= words[i].length <= 10
    board and words contain only lowercase English letters
    all words are distinct

Hint: running a separate board search per word is too slow; search for all
words at once.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        throw NotImplemented();
    }
};
