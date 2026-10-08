/*
153. Remove Duplicates from Sorted Array  ·  Easy  ·  Two Pointers
Source: https://leetcode.com/problems/remove-duplicates-from-sorted-array/

You get an integer array `nums` sorted in non-decreasing order. Remove the
repeated values in place, so that every distinct value is kept exactly once
and the kept values stay in their original (sorted) order.

If `nums` holds k distinct values, return k; the first k positions of `nums`
must then hold those values in increasing order. What is left in the positions
from k onwards doesn't matter.

Example 1:
    Input:  nums = [3, 3, 7]
    Output: 2             (nums starts with 3, 7: [3, 7, _])

Example 2:
    Input:  nums = [-2, -2, 0, 0, 0, 4, 9, 9]
    Output: 4             (nums starts with -2, 0, 4, 9)

Example 3:
    Input:  nums = [5]
    Output: 1

Constraints:
    1 <= nums.length <= 3 * 10^4
    -100 <= nums[i] <= 100
    nums is sorted in non-decreasing order

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        throw NotImplemented();
    }
};
