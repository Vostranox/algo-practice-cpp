/*
14. Trapping Rain Water  ·  Hard  ·  Two Pointers
Source: https://leetcode.com/problems/trapping-rain-water/

You get an array `height` of n non-negative integers describing an elevation
map: bar i is 1 unit wide and height[i] units tall, and the bars stand side by
side. After it rains, water collects in the dips between bars. Return the
total amount of water trapped.

Above bar i the water rises to the lower of (the tallest bar at or left of i)
and (the tallest bar at or right of i); water that isn't enclosed on both
sides runs off the ends.

Example 1:
    Input:  height = [3, 0, 2, 0, 4]
    Output: 7             (3 + 1 + 3 units above bars 1, 2 and 3)

Example 2:
    Input:  height = [5, 4, 1, 2]
    Output: 1             (only above bar 2; the right side is just 2 tall)

Example 3:
    Input:  height = [1, 2, 3]
    Output: 0

Constraints:
    1 <= height.length <= 2 * 10^4
    0 <= height[i] <= 10^5

Target: O(n) time; O(1) extra space with two pointers.
*/
#include "prelude.hpp"

class Solution {
public:
    int trap(vector<int>& height) {
        throw NotImplemented();
    }
};
