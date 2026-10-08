/*
42. Find the Duplicate Number  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/find-the-duplicate-number/

`nums` holds n + 1 integers, each between 1 and n inclusive. Exactly one value
occurs more than once (it may occur two times or many more); every other value
occurs at most once. Return the repeated value.

Rules: do not modify nums (the tests check this), and use only O(1) extra
space (so no hash set, no sorted copy).

Example 1:
    Input:  nums = [2, 4, 1, 3, 4]
    Output: 4

Example 2:
    Input:  nums = [3, 1, 3, 2]
    Output: 3

Example 3:
    Input:  nums = [2, 2, 2, 2, 2]
    Output: 2              (n = 4; the values 1, 3 and 4 don't appear at all)

Constraints:
    1 <= n <= 10^5
    nums.length == n + 1
    1 <= nums[i] <= n
    exactly one value appears two or more times; all others at most once

Target: O(n) time, O(1) extra space, nums unchanged.
Hint: think of i -> nums[i] as a linked list; why must it contain a cycle?
*/
#include "prelude.hpp"

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        throw NotImplemented();
    }
};
