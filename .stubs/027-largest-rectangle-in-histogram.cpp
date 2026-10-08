/*
27. Largest Rectangle in Histogram  ·  Hard  ·  Stack
Source: https://leetcode.com/problems/largest-rectangle-in-histogram/

`heights` describes a histogram: bar i is 1 unit wide and heights[i] units
tall, and the bars stand side by side with no gaps. Return the area of the
largest axis-aligned rectangle that fits inside the histogram. A rectangle may
cover several adjacent bars, but it can be no taller than the shortest bar it
covers.

Example 1:
    Input:  heights = [2, 4, 5, 3, 1, 3]
    Output: 9             (bars 1-3, heights 4, 5, 3, hold a rectangle 3 tall and 3 wide)

Example 2:
    Input:  heights = [6, 6]
    Output: 12

Example 3:
    Input:  heights = [0, 7, 0]
    Output: 7

Constraints:
    1 <= heights.length <= 10^5
    0 <= heights[i] <= 10^4

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        throw NotImplemented();
    }
};
