/*
3. Two Sum  ·  Easy  ·  Arrays & Hashing
Source: https://leetcode.com/problems/two-sum/

You get an integer array `nums` and an integer `target`. Find the two
positions i != j with nums[i] + nums[j] == target and return their indices
{i, j}. Every input has exactly one such pair. An element can't be paired with
itself (same index), but two different positions may hold equal values. The
two indices may be returned in either order.

Example 1:
    Input:  nums = [5, 2, 8], target = 10
    Output: [1, 2]        (2 + 8; using 5 twice is not allowed)

Example 2:
    Input:  nums = [-3, 4, 3, 90], target = 0
    Output: [0, 2]

Example 3:
    Input:  nums = [6, 6], target = 12
    Output: [0, 1]

Constraints:
    2 <= nums.length <= 10^4
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target <= 10^9
    exactly one valid pair exists

Target: O(n) time (better than checking every pair).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        throw NotImplemented();
    }
};
