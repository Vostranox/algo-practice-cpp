/*
218. Triangle  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/triangle/

`triangle` has n rows, and row i holds i + 1 numbers. A path starts at the
single number in row 0 and goes down one row at a time: from position j in
row i it may step to position j or position j + 1 in row i + 1. Return the
smallest possible sum of the numbers along a path from the top row to the
bottom row.

Example 1:
    Input:  triangle = [[3],
                        [7, 4],
                        [2, 9, 1],
                        [6, 5, 8, 4]]
    Output: 12      (3 + 4 + 1 + 4)

Example 2:
    Input:  triangle = [[1],
                        [2, 3],
                        [9, 8, 1]]
    Output: 5       (1 + 3 + 1: stepping to the smaller 2 first leads to 1 + 2 + 8 = 11)

Example 3:
    Input:  triangle = [[-5]]
    Output: -5

Constraints:
    1 <= triangle.length <= 200
    triangle[0].length == 1,  triangle[i].length == triangle[i - 1].length + 1
    -10^4 <= triangle[i][j] <= 10^4

Target: O(n^2) time, O(n) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        throw NotImplemented();
    }
};
