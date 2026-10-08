/*
170. Minimum Size Subarray Sum  ·  Medium  ·  Sliding Window
Source: https://leetcode.com/problems/minimum-size-subarray-sum/

You get an array of positive integers `nums` and a positive integer `target`.
Return the length of the shortest subarray (contiguous block of elements)
whose sum is at least `target`. If even the whole array falls short, return 0.

Example 1:
    Input:  target = 11, nums = [2, 7, 1, 8, 2, 8]
    Output: 3             ([7, 1, 8] sums to 16; no two neighbours reach 11)

Example 2:
    Input:  target = 6, nums = [1, 2, 6, 1]
    Output: 1             ([6])

Example 3:
    Input:  target = 50, nums = [5, 10, 15]
    Output: 0             (everything together is only 30)

Constraints:
    1 <= target <= 10^9
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4

Target: O(n) time. Follow-up: also find an O(n log n) solution.
*/
#include "prelude.hpp"

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        throw NotImplemented();
    }
};
