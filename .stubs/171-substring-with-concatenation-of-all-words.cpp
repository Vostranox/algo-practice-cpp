/*
171. Substring with Concatenation of All Words  ·  Hard  ·  Sliding Window
Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words/

You get a string `s` and a list `words` of strings that all have the same
length. A "concatenation" is any string formed by writing all the entries of
`words` one after another, each exactly once, in some order. If a word appears
several times in `words`, it must appear that many times in the concatenation.

Return every index i such that the substring of `s` that starts at i and has
length words.size() * words[0].size() is a concatenation. The indices can be
returned in any order. Matches may overlap and may start at any index, not
only at multiples of the word length.

Example 1:
    Input:  s = "dogcatcatdog", words = ["cat", "dog"]
    Output: [0, 6]        ("dogcat" and "catdog"; "catcat" at 3 doesn't count)

Example 2:
    Input:  s = "xyxyxy", words = ["xy", "xy"]
    Output: [0, 2]        (both copies of "xy" are needed)

Example 3:
    Input:  s = "zabbaz", words = ["ab", "ba"]
    Output: [1]           ("abba")

Constraints:
    1 <= s.length <= 10^4
    1 <= words.length <= 5000
    1 <= words[i].length <= 30, all words have the same length
    s and words[i] consist of lowercase English letters

Target: O(|s| * L) time, where L is the word length.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        throw NotImplemented();
    }
};
