/*
115. Target Sum  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/target-sum/

Put a '+' or a '-' sign in front of every number of `nums` (keeping their
order) and evaluate the resulting expression. Return how many of the 2^n sign
assignments evaluate to `target`. Assignments are counted separately even when
they look the same, e.g. "+0" and "-0" for a zero.

Example 1:
    Input:  nums = [2, 1, 1], target = 2
    Output: 2          (+2 +1 -1 and +2 -1 +1)

Example 2:
    Input:  nums = [1, 2, 3], target = 0
    Output: 2          (+1 +2 -3 and -1 -2 +3)

Example 3:
    Input:  nums = [0, 0, 1], target = 1
    Output: 4          (each 0 may take either sign)

Constraints:
    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums) <= 1000
    -1000 <= target <= 1000

Target: O(n * sum(nums)) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        throw NotImplemented();
    }
};
