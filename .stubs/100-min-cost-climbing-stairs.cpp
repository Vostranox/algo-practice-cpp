/*
100. Min Cost Climbing Stairs  ·  Easy  ·  1-D Dynamic Programming
Source: https://leetcode.com/problems/min-cost-climbing-stairs/

A staircase has steps 0 .. n-1, and `cost[i]` is the fee for step i: whenever
you stand on step i you pay cost[i] and may then move up either 1 or 2 steps.
You may begin on step 0 or on step 1. The goal ("the top") is position n, just
past the last step; it has no fee. Return the minimum total fee to reach the top.

Example 1:
    Input:  cost = [4, 9, 2]
    Output: 6          (start on step 0: pay 4, jump to step 2: pay 2, jump to the top)

Example 2:
    Input:  cost = [3, 1, 3, 1, 3, 1, 3]
    Output: 3          (start on step 1 and always jump 2: steps 1, 3, 5, then the top)

Example 3:
    Input:  cost = [10, 15]
    Output: 10

Constraints:
    2 <= cost.length <= 1000
    0 <= cost[i] <= 999

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        throw NotImplemented();
    }
};
