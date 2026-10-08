/*
26. Car Fleet  ·  Medium  ·  Stack
Source: https://leetcode.com/problems/car-fleet/

n cars drive along a single-lane road towards the same destination at mile
`target`. Car i starts at mile position[i] and drives at a constant speed[i]
(miles per hour). Every car starts behind the destination.

A car can never pass the car ahead of it. When a faster car catches up with a
slower car (or group of cars) ahead, it stays right behind it and from then on
drives at the slower speed; from that moment they count as being at the same
position.

A car fleet is a group of one or more cars that drive at the same position
with the same speed (a single car on its own is a fleet too). A car that
catches up with a fleet exactly at mile `target` still joins that fleet.

Return the number of car fleets that arrive at the destination.

Example 1:
    Input:  target = 20, position = [6, 16, 0, 10], speed = [2, 1, 4, 5]
    Output: 2
            The car at 10 catches the slow car at 16 at mile 17.5; they arrive
            together after 4 hours. The car at 0 catches the car at 6 at mile 12,
            and that pair arrives after 7 hours. So 2 fleets arrive.

Example 2:
    Input:  target = 10, position = [0, 5], speed = [2, 1]
    Output: 1             (both reach mile 10 after exactly 5 hours: they meet
                           at the destination, which counts as one fleet)

Example 3:
    Input:  target = 10, position = [0, 5], speed = [1, 2]
    Output: 2             (the car in front is faster; the gap only grows)

Constraints:
    n == position.length == speed.length
    1 <= n <= 10^5
    0 < target <= 10^6
    0 <= position[i] < target, and all positions are distinct
    0 < speed[i] <= 10^6

Target: O(n log n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        throw NotImplemented();
    }
};
