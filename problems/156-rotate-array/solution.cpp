/*
156. Rotate Array  ·  Medium  ·  Two Pointers
Source: https://leetcode.com/problems/rotate-array/

You get an integer array `nums` and a non-negative integer k. Rotate the array
k steps to the right, in place: in one step the last element moves to the
front and every other element moves one position to the right. Note that k
can be larger than the length of the array. The function returns nothing; the
result is read from `nums`.

Example 1:
    Input:  nums = [1, 2, 3, 4, 5, 6], k = 2
    After:  nums = [5, 6, 1, 2, 3, 4]

Example 2:
    Input:  nums = [10, -20, 30], k = 4
    After:  nums = [30, 10, -20]     (3 steps give back the original, so 4 steps = 1 step)

Example 3:
    Input:  nums = [9, 8], k = 0
    After:  nums = [9, 8]

Constraints:
    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1
    0 <= k <= 10^5

Target: O(n) time. Follow-up: O(1) extra space (there are several ways).
*/
#include "prelude.hpp"

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        throw NotImplemented();
    }
};
