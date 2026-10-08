/*
11. Two Sum II - Input Array Is Sorted  ·  Medium  ·  Two Pointers
Source: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

You get an integer array `numbers` sorted in non-decreasing order, and an
integer `target`. Exactly one pair of different positions holds two numbers
that add up to `target`. Return that pair as 1-indexed positions
{index1, index2} with 1 <= index1 < index2 <= numbers.length.

You may not use the same element twice, and your solution may only use O(1)
extra space (no hash map / set of seen values).

Example 1:
    Input:  numbers = [1, 3, 4, 7, 9], target = 11
    Output: [3, 4]        (4 + 7; positions are counted from 1)

Example 2:
    Input:  numbers = [-5, -2, 0, 3], target = -7
    Output: [1, 2]

Example 3:
    Input:  numbers = [2, 3, 3, 8], target = 6
    Output: [2, 3]        (equal values at two different positions)

Constraints:
    2 <= numbers.length <= 3 * 10^4
    -1000 <= numbers[i] <= 1000
    numbers is sorted in non-decreasing order
    -1000 <= target <= 1000
    exactly one valid pair exists

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        throw NotImplemented();
    }
};
