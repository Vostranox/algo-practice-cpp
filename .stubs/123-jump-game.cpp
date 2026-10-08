/*
123. Jump Game  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/jump-game/

You stand on index 0 of an array `nums` of non-negative integers. From index
i you may jump forward by any distance from 1 up to nums[i] (so nums[i] == 0
means you are stuck there). Return true if some sequence of jumps lands you on
the last index, otherwise false.

Example 1:
    Input:  nums = [1, 3, 0, 0, 2]
    Output: true          (0 -> 1, then jump 3 from index 1 to index 4)

Example 2:
    Input:  nums = [2, 1, 0, 4]
    Output: false         (every route ends on index 2, whose value is 0)

Example 3:
    Input:  nums = [0]
    Output: true          (you already stand on the last index)

Constraints:
    1 <= nums.length <= 10^4
    0 <= nums[i] <= 10^5

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    bool canJump(vector<int>& nums) {
        throw NotImplemented();
    }
};
