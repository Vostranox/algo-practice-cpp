/*
20. Sliding Window Maximum  ·  Hard  ·  Sliding Window
Source: https://leetcode.com/problems/sliding-window-maximum/

You get an integer array `nums` and a window size `k`. A window covering k
consecutive elements starts at the left end of `nums` and moves right one
position at a time until it reaches the right end. Return an array with the
maximum of each window, in order (nums.length - k + 1 values).

Example 1:
    Input:  nums = [4, 2, 12, 3, 8, 1, 7], k = 3
    Output: [12, 12, 12, 8, 8]
            windows: [4 2 12] [2 12 3] [12 3 8] [3 8 1] [8 1 7]

Example 2:
    Input:  nums = [9, 8, 7, 6], k = 2
    Output: [9, 8, 7]

Example 3:
    Input:  nums = [5], k = 1
    Output: [5]

Constraints:
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    1 <= k <= nums.length

Target: O(n) time (recomputing every window's max is O(n * k)).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        throw NotImplemented();
    }
};
