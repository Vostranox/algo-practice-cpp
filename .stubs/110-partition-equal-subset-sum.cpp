/*
110. Partition Equal Subset Sum  ·  Medium  ·  1-D Dynamic Programming
Source: https://leetcode.com/problems/partition-equal-subset-sum/

Decide whether the elements of `nums` can be split into two groups with equal
sums, every element going into exactly one of the two groups. Return true or
false.

Example 1:
    Input:  nums = [3, 1, 5, 9, 4, 2]
    Output: true       ({9, 3} and {1, 5, 4, 2} both sum to 12)

Example 2:
    Input:  nums = [2, 3, 7]
    Output: false      (the total 12 is even, but no subset sums to 6)

Example 3:
    Input:  nums = [8]
    Output: false

Constraints:
    1 <= nums.length <= 200
    1 <= nums[i] <= 100

Target: O(n * sum(nums)) time, O(sum(nums)) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        throw NotImplemented();
    }
};
