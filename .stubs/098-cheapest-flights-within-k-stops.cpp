/*
98. Cheapest Flights Within K Stops  ·  Medium  ·  Advanced Graphs
Source: https://leetcode.com/problems/cheapest-flights-within-k-stops/

There are n cities, numbered 0 .. n - 1, and one-way flights, where
flights[i] = {from, to, price}. Return the cheapest total price of a route from
city `src` to city `dst` that makes at most k stops (a stop is an intermediate
city, so the route uses at most k + 1 flights). Return -1 if no such route
exists.

Example 1:
    Input:  n = 4, flights = [[0, 1, 100], [1, 2, 100], [2, 3, 100], [0, 2, 500], [1, 3, 600]],
            src = 0, dst = 3, k = 1
    Output: 600     (0 -> 2 -> 3; the 300 route 0 -> 1 -> 2 -> 3 needs two stops)

Example 2:
    Input:  the same flights, src = 0, dst = 3, k = 2
    Output: 300

Example 3:
    Input:  n = 3, flights = [[0, 1, 50]], src = 0, dst = 2, k = 1
    Output: -1

Constraints:
    1 <= n <= 100
    0 <= flights.length <= n * (n - 1) / 2
    flights[i].size() == 3,  0 <= from, to < n,  from != to,  1 <= price <= 10^4
    there is at most one flight between any two cities
    0 <= src, dst, k < n,  src != dst

Target: O(k * flights.length) time (Bellman-Ford limited to k + 1 rounds).
*/
#include "prelude.hpp"

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        throw NotImplemented();
    }
};
