/*
13. Container With Most Water  ·  Medium  ·  Two Pointers
Source: https://leetcode.com/problems/container-with-most-water/

You get an array `height` of n non-negative integers. Picture n vertical
lines: line i stands at x = i and is height[i] tall. Any two lines i < j
together with the x-axis form a container that holds

    min(height[i], height[j]) * (j - i)

units of water (the container can't be tilted, so the shorter line decides
the water level). Return the largest amount of water any container can hold.

Example 1:
    Input:  height = [2, 5, 4, 1, 6, 3]
    Output: 15            (lines 1 and 4: min(5, 6) * (4 - 1))

Example 2:
    Input:  height = [6, 1, 1, 1, 1, 1, 2]
    Output: 12            (lines 0 and 6: min(6, 2) * 6)

Example 3:
    Input:  height = [7, 7]
    Output: 7

Constraints:
    2 <= height.length <= 10^5
    0 <= height[i] <= 10^4

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxArea(vector<int>& height) {
        throw NotImplemented();
    }
};
