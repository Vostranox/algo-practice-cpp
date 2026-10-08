/*
4. Group Anagrams  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/group-anagrams/

You get an array of strings `strs`. Split them into groups so that two strings
are in the same group exactly when they are anagrams of each other (same
letters with the same counts). Return the list of groups.

Every input string must appear in exactly one group, as many times as it
appears in the input (duplicates stay). The groups can be returned in any
order, and the strings inside a group in any order.

Example 1:
    Input:  strs = ["stop", "pots", "cat", "tops", "act", "dog"]
    Output: [["stop", "pots", "tops"], ["cat", "act"], ["dog"]]

Example 2:
    Input:  strs = ["ab", "ba", "ab", "c"]
    Output: [["ab", "ba", "ab"], ["c"]]

Example 3:
    Input:  strs = [""]
    Output: [[""]]

Constraints:
    1 <= strs.length <= 10^4
    0 <= strs[i].length <= 100
    strs[i] consists of lowercase English letters

Target: O(n * m) time, where m is the maximum string length
(O(n * m log m) by sorting each string is fine too).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        throw NotImplemented();
    }
};
