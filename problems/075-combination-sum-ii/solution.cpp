/*
75. Combination Sum II  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/combination-sum-ii/

Given an array `candidates` of positive integers (values may repeat) and a
positive integer `target`, return every distinct combination of candidates that
adds up to target. Each array element may be used at most once -- a value that
appears twice in candidates can be used at most twice.

Two combinations are the same if they contain the same values the same number
of times, and the answer must not contain the same combination twice. Return the
combinations in any order (the numbers inside a combination in any order too),
or an empty list if there are none.

Example 1:
    Input:  candidates = [4, 1, 3, 1, 2, 5], target = 6
    Output: [[1, 5], [2, 4], [1, 1, 4], [1, 2, 3]]

Example 2:
    Input:  candidates = [3, 3, 3], target = 6
    Output: [[3, 3]]                (only once, although three pairs of 3s exist)

Example 3:
    Input:  candidates = [5, 7], target = 3
    Output: []

Constraints:
    1 <= candidates.length <= 100
    1 <= candidates[i] <= 50
    1 <= target <= 30

Target: backtracking over the sorted candidates that never starts two branches
with the same value at the same depth. Generating all subsets and removing
duplicates afterwards is far too slow with 100 candidates.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        throw NotImplemented();
    }
};
