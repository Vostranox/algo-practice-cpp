/*
160. Candy  ·  Hard  ·  Greedy
Source: https://leetcode.com/problems/candy/

n children stand in a row and child i has the rating ratings[i]. You hand out
candies under two rules:
  - every child gets at least one candy;
  - a child with a strictly higher rating than a neighbour gets more candies
    than that neighbour.
Neighbours with equal ratings don't constrain each other. Return the smallest
total number of candies that satisfies both rules.

Example 1:
    Input:  ratings = [2, 5, 3]
    Output: 4       (1, 2, 1)

Example 2:
    Input:  ratings = [4, 3, 2, 2, 6]
    Output: 9       (3, 2, 1, 1, 2)

Example 3:
    Input:  ratings = [1, 3, 5, 5, 5, 2]
    Output: 10      (1, 2, 3, 1, 2, 1: the middle 5 sits between equal ratings, so 1 is enough)

Constraints:
    1 <= ratings.length <= 2 * 10^4
    0 <= ratings[i] <= 2 * 10^4

Target: O(n) time (O(1) extra space is possible).
*/
#include "prelude.hpp"

class Solution {
public:
    int candy(vector<int>& ratings) {
        throw NotImplemented();
    }
};
