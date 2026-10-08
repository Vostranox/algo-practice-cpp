/*
97. Alien Dictionary  ·  Hard  ·  Advanced Graphs
Source: https://leetcode.com/problems/alien-dictionary/

An alien language uses lowercase English letters, but in an unknown
alphabetical order. You get a list of `words` that is claimed to be sorted
lexicographically by the rules of that language: two words are compared at the
first position where they differ (the letter that comes earlier in the alien
alphabet wins), and if one word is a proper prefix of the other, the shorter
word comes first.

Return a string containing every distinct letter that appears in `words`
exactly once, in an alien-alphabet order under which `words` really is sorted.
If several orders work, return any of them. If no order works, return "".
(For example, a word followed by its own proper prefix, like ["ab", "a"], can
never be sorted.)

Example 1:
    Input:  words = ["bca", "aaa", "acb"]
    Output: "bac"       (b before a from the first pair, a before c from the second)

Example 2:
    Input:  words = ["pq", "pr", "s"]
    Output: "pqrs"      (any order with q before r and p before s is accepted,
                         e.g. "qprs" or "pqsr")

Example 3:
    Input:  words = ["x", "z", "x"]
    Output: ""          (x before z and z before x)

Constraints:
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consists of lowercase English letters

Target: O(C) time, C = total number of characters (build a graph, topological sort).
*/
#include "prelude.hpp"

class Solution {
public:
    string alienOrder(vector<string>& words) {
        throw NotImplemented();
    }
};
