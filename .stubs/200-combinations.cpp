/*
200. Combinations  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/combinations/

Given two integers n and k, return every way to choose k different numbers from
1, 2, ..., n (all the k-element combinations). Each combination must appear
exactly once. Return the combinations in any order; the numbers inside a
combination may also be in any order.

Example 1:
    Input:  n = 4, k = 2
    Output: [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]

Example 2:
    Input:  n = 3, k = 3
    Output: [[1, 2, 3]]

Example 3:
    Input:  n = 5, k = 1
    Output: [[1], [2], [3], [4], [5]]

Constraints:
    1 <= n <= 20
    1 <= k <= n

Target: O(k * C(n, k)) -- backtracking that extends a partial combination only
with numbers larger than its last one.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        throw NotImplemented();
    }
};
