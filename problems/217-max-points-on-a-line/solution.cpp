/*
217. Max Points on a Line  ·  Hard  ·  Math & Geometry
Source: https://leetcode.com/problems/max-points-on-a-line/

You get `points`, a list of distinct points in the plane, each given as
[x, y] with integer coordinates. Return the largest number of these points
that lie together on one straight line (of any direction: horizontal,
vertical or slanted).

Example 1:
    Input:  points = [[2, 1], [4, 2], [6, 3], [3, 5]]
    Output: 3     ((2,1), (4,2), (6,3) lie on y = x / 2)

Example 2:
    Input:  points = [[-3, 4], [0, 4], [5, 4], [2, 1], [2, 7], [2, -6], [2, 0]]
    Output: 4     (the vertical line x = 2; the horizontal line y = 4 has only 3)

Example 3:
    Input:  points = [[7, -3]]
    Output: 1

Constraints:
    1 <= points.length <= 300
    points[i].length == 2
    -10^4 <= points[i][0], points[i][1] <= 10^4
    all points are distinct

Target: O(n^2) time with hashing (n = points.length).
Hint: comparing slopes as floating-point numbers (floats, or doubles with a
tolerance) is fragile, and the tests include nearly parallel lines; integer
arithmetic compares directions exactly.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        throw NotImplemented();
    }
};
