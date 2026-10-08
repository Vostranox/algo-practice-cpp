/*
199. Minimum Genetic Mutation  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/minimum-genetic-mutation/

A gene is a string of 8 characters, each one of 'A', 'C', 'G' and 'T'. A
mutation changes exactly one character of a gene to a different letter
("ACGTACGT" -> "ACGTACCT" is one mutation). Only the genes listed in `bank` are
valid: every gene produced by a mutation, endGene included, must be in the bank
(startGene itself doesn't have to be).

Return the fewest mutations that turn `startGene` into `endGene`, or -1 if
it can't be done. When startGene == endGene the answer is 0.

Example 1:
    Input:  startGene = "AAAAACCC", endGene = "AAAAAGGC",
            bank = ["AAAAAGCC", "AAAAAGGC"]
    Output: 2       (AAAAACCC -> AAAAAGCC -> AAAAAGGC)

Example 2:
    Input:  startGene = "GATTACAA", endGene = "GATTACCA",
            bank = ["GATTACAT", "CATTACAA"]
    Output: -1      (endGene is not in the bank)

Example 3:
    Input:  startGene = "AAAAAAAA", endGene = "AAAAAATT",
            bank = ["AAAAAATT", "GAAAAAAA", "GAAAAATA", "GAAAAATT"]
    Output: 4       (neither AAAAAATA nor AAAAAAAT is valid, so take the detour
                     AAAAAAAA -> GAAAAAAA -> GAAAAATA -> GAAAAATT -> AAAAAATT)

Constraints:
    0 <= bank.length <= 10
    startGene.length == endGene.length == bank[i].length == 8
    every gene consists of the letters 'A', 'C', 'G', 'T'

Target: breadth-first search over the bank, O(B * 8 * 4) neighbour checks with a hash set
        (or O(B^2 * 8) comparing genes pairwise).
*/
#include "prelude.hpp"

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        throw NotImplemented();
    }
};
