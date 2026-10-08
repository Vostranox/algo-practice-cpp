/*
158. H-Index  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/h-index/

A researcher has written n papers; `citations[i]` is how often paper i has
been cited. Their h-index is the largest number h such that at least h of the
papers have been cited at least h times each. Return the h-index.

Example 1:
    Input:  citations = [4, 0, 6, 1, 5]
    Output: 3             (three papers have >= 3 citations; there aren't four
                           papers with >= 4 citations)

Example 2:
    Input:  citations = [2, 2, 2]
    Output: 2

Example 3:
    Input:  citations = [0, 0]
    Output: 0

Constraints:
    1 <= citations.length <= 5000
    0 <= citations[i] <= 1000

Target: O(n log n) time; O(n) is possible.
*/
#include "prelude.hpp"

class Solution {
public:
    int hIndex(vector<int>& citations) {
        throw NotImplemented();
    }
};
