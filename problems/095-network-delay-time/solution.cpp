/*
95. Network Delay Time  ·  Medium  ·  Advanced Graphs
Source: https://leetcode.com/problems/network-delay-time/

A network has n nodes labelled 1..n. times[i] = {u, v, w} is a directed link:
a signal sent from u reaches v after w time units. A signal starts at node k
at time 0 and spreads along all links. Return the time at which the last node
receives it, i.e. the largest shortest-path distance from k. If some node never
receives the signal, return -1.

Example 1:
    Input:  times = [[1, 2, 4], [1, 3, 1], [3, 2, 2], [2, 4, 1]], n = 4, k = 1
    Output: 4       (node 3 at 1, node 2 at 3 via node 3, node 4 at 4)

Example 2:
    Input:  times = [[1, 2, 5]], n = 3, k = 1
    Output: -1      (nothing leads to node 3)

Example 3:
    Input:  times = [[1, 2, 0], [2, 3, 0]], n = 3, k = 1
    Output: 0       (links can take no time at all)

Constraints:
    1 <= k <= n <= 100
    1 <= times.length <= 6000
    times[i].size() == 3,  1 <= u, v <= n,  u != v,  0 <= w <= 100
    no two links have the same (u, v)

Target: O(E log V) time (Dijkstra with a heap).
*/
#include "prelude.hpp"

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        throw NotImplemented();
    }
};
