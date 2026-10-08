/*
167. Find the Index of the First Occurrence in a String  ·  Easy  ·  Arrays & Hashing
Source: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

You get two strings `haystack` and `needle`. Return the smallest index i such
that `needle` appears in `haystack` starting at position i, or -1 if `needle`
does not appear in `haystack` at all.

Example 1:
    Input:  haystack = "hello world", needle = "o"
    Output: 4             (the first of the two o's)

Example 2:
    Input:  haystack = "mississippi", needle = "issip"
    Output: 4

Example 3:
    Input:  haystack = "abc", needle = "abcd"
    Output: -1

Constraints:
    1 <= haystack.length, needle.length <= 10^4
    haystack and needle consist of lowercase English letters

Comparing needle at every start position, O(n * m), is fine here.
Follow-up: can you do it in O(n + m) time (e.g. with the KMP algorithm)?
*/
#include "prelude.hpp"

class Solution {
public:
    int strStr(string haystack, string needle) {
        throw NotImplemented();
    }
};
