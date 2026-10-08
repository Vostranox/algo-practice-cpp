/*
169. Is Subsequence  ·  Easy  ·  Two Pointers
Source: https://leetcode.com/problems/is-subsequence/

You get two strings `s` and `t`. Return true if `s` is a subsequence of `t`,
i.e. if `s` can be obtained from `t` by deleting some (possibly none, possibly
all) of its characters without changing the order of the remaining ones.
Otherwise return false.

Example 1:
    Input:  s = "rot", t = "parrot"
    Output: true          (pa[r]r[o][t])

Example 2:
    Input:  s = "tar", t = "parrot"
    Output: false         (the only 't' is the last letter of t)

Example 3:
    Input:  s = "", t = "abc"
    Output: true          (the empty string is a subsequence of every string)

Constraints:
    0 <= s.length <= 100
    0 <= t.length <= 10^4
    s and t consist of lowercase English letters

Target: O(|s| + |t|) time.
Follow-up: if there were a huge number of strings s to test against the same
t, how would you preprocess t so that each check is fast?
*/
#include "prelude.hpp"

class Solution {
public:
    bool isSubsequence(string s, string t) {
        throw NotImplemented();
    }
};
