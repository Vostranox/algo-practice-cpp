/*
128. Partition Labels  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/partition-labels/

Cut the string `s` into as many consecutive pieces as possible such that no
letter shows up in more than one piece. (Joining the pieces back together in
order must give `s` again.) Return the lengths of the pieces, from left to
right.

Example 1:
    Input:  s = "abcbaxyzyq"
    Output: [5, 1, 3, 1]  ("abcba" | "x" | "yzy" | "q")

Example 2:
    Input:  s = "abcdabef"
    Output: [6, 1, 1]     ("abcdab" | "e" | "f")

Example 3:
    Input:  s = "aaaa"
    Output: [4]

Constraints:
    1 <= s.length <= 500
    s consists of lowercase English letters

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> partitionLabels(string s) {
        throw NotImplemented();
    }
};
