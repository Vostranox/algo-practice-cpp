/*
29. Search a 2D Matrix  ·  Medium  ·  Binary Search
Source: https://leetcode.com/problems/search-a-2d-matrix/

`matrix` is an m x n grid of integers with two properties:
    - every row is sorted in non-decreasing order, and
    - the first value of each row is greater than the last value of the row above.
(So reading the rows one after another gives a single sorted sequence.)

Return true if `target` appears anywhere in the matrix, otherwise false.

Your algorithm must run in O(log(m * n)) time. (The tests call it ~10^6 times on
a 100 x 100 matrix, which catches scanning every cell; an O(m + n) walk is too
fast to be told apart at this size, so hold yourself to the target.)

Example 1:
    Input:  matrix = [[ 1,  4,  6,  9],
                      [12, 13, 20, 25],
                      [31, 40, 41, 50]], target = 20
    Output: true

Example 2:
    Input:  the same matrix, target = 10
    Output: false

Example 3:
    Input:  matrix = [[-5]], target = -5
    Output: true

Constraints:
    m == matrix.length, n == matrix[i].length
    1 <= m, n <= 100
    -10^4 <= matrix[i][j], target <= 10^4
*/
#include "prelude.hpp"

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        throw NotImplemented();
    }
};
