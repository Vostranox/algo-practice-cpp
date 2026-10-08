/*
72. Combination Sum  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/combination-sum/

Given an array `candidates` of distinct positive integers and a positive integer
`target`, return every combination of candidate values that adds up to target.
A value may be used any number of times. Two combinations count as the same if
every value is used the same number of times in both -- [2, 3] and [3, 2] are
the same combination, and the answer must not contain it twice.

Return the combinations in any order; the numbers inside a combination may also
be in any order. Return an empty list if no combination adds up to target.

Example 1:
    Input:  candidates = [3, 4, 5], target = 8
    Output: [[3, 5], [4, 4]]

Example 2:
    Input:  candidates = [2, 7], target = 11
    Output: [[2, 2, 7]]

Example 3:
    Input:  candidates = [6, 9], target = 5
    Output: []

Constraints:
    1 <= candidates.length <= 30
    2 <= candidates[i] <= 40, all distinct
    1 <= target <= 40
    the inputs are chosen so that there are fewer than 150 combinations

Target: backtracking where, once you move past a candidate, you never pick it
again (this is what stops [2, 3] and [3, 2] from both being generated).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        throw NotImplemented();
    }
};
