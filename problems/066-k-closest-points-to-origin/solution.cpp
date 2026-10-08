/*
66. K Closest Points to Origin  ·  Medium  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/k-closest-points-to-origin/

You get an array of points on the plane, points[i] = [x_i, y_i], and an integer
k. Return the k points that are closest to the origin (0, 0), using the
ordinary Euclidean distance sqrt(x^2 + y^2).

The inputs guarantee the answer is unique: every point in the answer is strictly
closer than every point left out (ties are only possible among the chosen
points, or among the points left out). Return the points in any order, each as
an [x, y] pair. If the same point appears several times in `points`, each copy
is a separate point.

Example 1:
    Input:  points = [[2, -1], [0, 3], [-1, -1]], k = 2
    Output: [[-1, -1], [2, -1]]      (squared distances: 5, 9, 2)

Example 2:
    Input:  points = [[4, 4], [-5, 0], [1, -6], [3, -2]], k = 1
    Output: [[3, -2]]                (squared distances: 32, 25, 37, 13)

Example 3:
    Input:  points = [[1, 2], [2, 1], [5, 5]], k = 2
    Output: [[1, 2], [2, 1]]         (a tie inside the answer is fine)

Constraints:
    1 <= k <= points.length <= 10^4
    -10^4 <= x_i, y_i <= 10^4

Target: O(n log k) with a max-heap of size k (sorting everything, O(n log n),
also passes; quickselect gives O(n) on average).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        throw NotImplemented();
    }
};
