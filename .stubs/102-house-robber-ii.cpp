/*
102. House Robber II  ·  Medium  ·  1-D Dynamic Programming
Source: https://leetcode.com/problems/house-robber-ii/

Same as House Robber, but the houses stand in a circle: house i is next to
house i-1 and house i+1, and the last house is also next to the first one.
`nums[i]` is the money in house i. Choose houses so that no two chosen houses
are next to each other and return the largest total you can take.
(With a single house there is no neighbour, so you can take it.)

Example 1:
    Input:  nums = [3, 4, 3]
    Output: 4          (the two 3s are neighbours across the circle)

Example 2:
    Input:  nums = [2, 9, 4, 1, 8]
    Output: 17         (houses 1 and 4)

Example 3:
    Input:  nums = [6, 2, 1, 7]
    Output: 9          (houses 1 and 3; 6 and 7 can't both be taken)

Constraints:
    1 <= nums.length <= 100
    0 <= nums[i] <= 1000

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int rob(vector<int>& nums) {
        throw NotImplemented();
    }
};
