/*
62. Design Add and Search Words Data Structure  ·  Medium  ·  Tries
Source: https://leetcode.com/problems/design-add-and-search-words-data-structure/

Design a word store whose search supports a single-letter wildcard.

    WordDictionary()           creates an empty store
    addWord(word)              adds word
    search(word) -> bool       true if some added word matches word, where every
                               '.' in word matches any one letter and every
                               other character must be equal. The whole word
                               must match (same length; no prefix matches).

Example:
    WordDictionary()
    addWord("lamp"); addWord("limp"); addWord("lamb")
    search("lump")   -> false
    search("l.mp")   -> true    (lamp, limp)
    search("..mb")   -> true    (lamb)
    search("lam")    -> false   (a prefix is not a match)
    search("l..p")   -> true
    search("lamp.")  -> false   ('.' must match exactly one letter)

Constraints:
    1 <= word.length <= 25
    addWord's word consists of lowercase English letters
    search's word consists of lowercase English letters and '.'
    a search word contains at most 2 dots
    at most 10^4 calls in total to addWord and search
*/
#include "prelude.hpp"

class WordDictionary {
public:
    WordDictionary() {
    }

    void addWord(string word) {
        throw NotImplemented();
    }

    bool search(string word) {
        throw NotImplemented();
    }
};
