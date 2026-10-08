/*
176. Contains Duplicate II  ·  Easy  ·  Sliding Window
Source: https://leetcode.com/problems/contains-duplicate-ii/

You get an integer array `nums` and an integer k. Return true if there are two
different indices i and j with nums[i] == nums[j] and |i - j| <= k, i.e. if
some value repeats within a distance of at most k positions. Otherwise return
false.

Example 1:
    Input:  nums = [4, 1, 7, 4], k = 3
    Output: true          (the two 4's are at indices 0 and 3)

Example 2:
    Input:  nums = [4, 1, 7, 4], k = 2
    Output: false         (they are 3 apart)

Example 3:
    Input:  nums = [6, 3, 3], k = 1
    Output: true

Constraints:
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    0 <= k <= 10^5

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        throw NotImplemented();
    }
};
