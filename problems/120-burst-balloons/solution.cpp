/*
120. Burst Balloons  ·  Hard  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/burst-balloons/

A row of balloons carries the numbers `nums`. You burst all of them, one at a
time, in an order of your choice. Bursting a balloon earns
left * value * right coins, where value is its own number and left/right are
the numbers on its current neighbours, i.e. the nearest balloons on each side
that have not been burst yet. A missing neighbour (past either end of the row)
counts as 1. Return the maximum total number of coins.

Example 1:
    Input:  nums = [2, 4, 3]
    Output: 33         (burst 4: 2*4*3 = 24, then 2: 1*2*3 = 6, then 3: 1*3*1 = 3)

Example 2:
    Input:  nums = [1, 5]
    Output: 10         (burst 1: 1*1*5 = 5, then 5: 1*5*1 = 5)

Example 3:
    Input:  nums = [5]
    Output: 5

Constraints:
    1 <= nums.length <= 300
    0 <= nums[i] <= 100

Target: O(n^3) time, O(n^2) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        throw NotImplemented();
    }
};
