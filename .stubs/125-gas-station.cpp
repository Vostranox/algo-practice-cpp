/*
125. Gas Station  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/gas-station/

n gas stations sit on a circular road, numbered 0..n-1 in driving order.
Stopping at station i gives you gas[i] units of fuel, and driving from
station i to the next one, (i + 1) % n, burns cost[i] units. The tank has no
capacity limit.

You start at some station with an empty tank, take its fuel, and drive around
the loop, refuelling at every station, until you are back where you started.
You may not drive a leg with less fuel than it costs (ending a leg with
exactly 0 is fine). Return the index of the station you can start from to
complete the loop, or -1 if no start works. The inputs guarantee that when a
working start exists, it is the only one.

Example 1:
    Input:  gas = [2, 3, 4], cost = [3, 4, 1]
    Output: 2
            Start at 2 with 4 fuel -> reach 0 with 3, refuel to 5 -> reach 1
            with 2, refuel to 5 -> reach 2 with 1. Starting at 0 or 1 fails on
            the very first leg.

Example 2:
    Input:  gas = [1, 2, 3], cost = [2, 3, 2]
    Output: -1            (the whole loop costs 7 but only 6 fuel exists)

Example 3:
    Input:  gas = [5], cost = [4]
    Output: 0             (one station: the "loop" is a single leg back to it)

Constraints:
    n == gas.length == cost.length
    1 <= n <= 10^5
    0 <= gas[i], cost[i] <= 10^4
    at most one starting station works

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        throw NotImplemented();
    }
};
