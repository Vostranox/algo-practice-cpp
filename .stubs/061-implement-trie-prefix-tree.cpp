/*
61. Implement Trie (Prefix Tree)  ·  Medium  ·  Tries
Source: https://leetcode.com/problems/implement-trie-prefix-tree/

Implement a trie (prefix tree), a tree that stores strings letter by letter so
that words sharing a prefix share the path for it.

    Trie()                        creates an empty trie
    insert(word)                  adds word (inserting it again changes nothing)
    search(word) -> bool          true if word itself was inserted before
    startsWith(prefix) -> bool    true if some inserted word begins with prefix
                                  (a word counts as a prefix of itself)

Example:
    Trie()
    insert("card")
    search("car")       -> false   (only "card" was inserted)
    startsWith("car")   -> true
    insert("car")
    search("car")       -> true
    startsWith("cart")  -> false
    search("card")      -> true

Constraints:
    1 <= word.length, prefix.length <= 2000
    word and prefix consist only of lowercase English letters
    at most 3 * 10^4 calls in total to insert, search and startsWith

Target: each operation O(length of its argument).
*/
#include "prelude.hpp"

class Trie {
public:
    Trie() {
    }

    void insert(string word) {
        throw NotImplemented();
    }

    bool search(string word) {
        throw NotImplemented();
    }

    bool startsWith(string prefix) {
        throw NotImplemented();
    }
};
