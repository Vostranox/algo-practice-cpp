/*
173. Ransom Note  ·  Easy  ·  Arrays & Hashing
Source: https://leetcode.com/problems/ransom-note/

You want to write `ransomNote` by cutting letters out of `magazine`. Every
letter of the magazine can be used at most once. Return true if the note can
be built this way, otherwise false.

Example 1:
    Input:  ransomNote = "cab", magazine = "abcd"
    Output: true

Example 2:
    Input:  ransomNote = "noon", magazine = "onion"
    Output: true          (the magazine has two n's and two o's)

Example 3:
    Input:  ransomNote = "aa", magazine = "ab"
    Output: false         (only one a to cut out)

Constraints:
    1 <= ransomNote.length, magazine.length <= 10^5
    ransomNote and magazine consist of lowercase English letters

Target: O(m + n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        throw NotImplemented();
    }
};
