/*
154. Remove Duplicates from Sorted Array II  ·  Medium  ·  Two Pointers
Source: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

You get an integer array `nums` sorted in non-decreasing order. Thin it out in
place so that every value occurs at most twice: a value that occurs once stays
once, a value that occurs two or more times is kept exactly twice. The kept
values stay in their original (sorted) order.

If k values are kept, return k; the first k positions of `nums` must then hold
them in sorted order. What is left in the positions from k onwards doesn't
matter.

Example 1:
    Input:  nums = [4, 4, 4, 6]
    Output: 3             (nums starts with 4, 4, 6: [4, 4, 6, _])

Example 2:
    Input:  nums = [-1, 0, 0, 0, 0, 2, 3, 3, 3]
    Output: 6             (nums starts with -1, 0, 0, 2, 3, 3)

Example 3:
    Input:  nums = [8, 9]
    Output: 2

Constraints:
    1 <= nums.length <= 3 * 10^4
    -10^4 <= nums[i] <= 10^4
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
