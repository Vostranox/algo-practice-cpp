/*
12. 3Sum  ·  Medium  ·  Two Pointers
Source: https://leetcode.com/problems/3sum/

You get an integer array `nums`. Return every triplet [a, b, c] of values
taken from three DIFFERENT positions of `nums` with a + b + c == 0.

The output must not contain the same triplet twice: two triplets count as the
same if they hold the same three values (e.g. [-1, 0, 1] and [0, 1, -1]).
The triplets can be listed in any order, and the values inside each triplet
in any order. Return an empty list if there is no such triplet.

Example 1:
    Input:  nums = [-2, 0, 1, 1, 2]
    Output: [[-2, 0, 2], [-2, 1, 1]]     (1 is used twice: it occurs twice)

Example 2:
    Input:  nums = [1, 2, -4, 5]
    Output: []

Example 3:
    Input:  nums = [0, 0, 0, 0]
    Output: [[0, 0, 0]]                  (listed only once)

Constraints:
    3 <= nums.length <= 3000
    -10^5 <= nums[i] <= 10^5

Target: O(n^2) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        throw NotImplemented();
    }
};
