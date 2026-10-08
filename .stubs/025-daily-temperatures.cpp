/*
25. Daily Temperatures  ·  Medium  ·  Stack
Source: https://leetcode.com/problems/daily-temperatures/

temperatures[i] is the temperature measured on day i. For every day, work out
how many days you must wait after it until a strictly warmer day arrives; if
no later day is warmer, the wait is 0.

Return the waits as a vector of the same length (answer[i] belongs to day i).

Example 1:
    Input:  temperatures = [60, 58, 59, 64, 61, 61, 70]
    Output: [3, 1, 1, 3, 2, 1, 0]
            (day 4 is 61: day 5 is also 61, not warmer, so it waits 2 days for 70)

Example 2:
    Input:  temperatures = [40, 50, 60]
    Output: [1, 1, 0]

Example 3:
    Input:  temperatures = [90, 80, 80, 70]
    Output: [0, 0, 0, 0]  (it never gets warmer)

Constraints:
    1 <= temperatures.length <= 10^5
    30 <= temperatures[i] <= 100

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        throw NotImplemented();
    }
};
