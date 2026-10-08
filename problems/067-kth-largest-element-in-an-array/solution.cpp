/*
67. Kth Largest Element in an Array  ·  Medium  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/kth-largest-element-in-an-array/

Given an integer array `nums` and an integer k, return the k-th largest element:
the value that would sit at position k (1-based) if nums were sorted from
largest to smallest. Repeated values count separately -- in [5, 5, 3] the 2nd
largest is 5, not 3.

Can you do it without sorting the whole array?

Example 1:
    Input:  nums = [7, 2, 9, 4, 1], k = 2
    Output: 7

Example 2:
    Input:  nums = [6, 3, 6, 6, 2, 8], k = 3
    Output: 6        (descending: 8 6 6 6 3 2)

Example 3:
    Input:  nums = [-4], k = 1
    Output: -4

Constraints:
    1 <= k <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

Target: O(n log k) with a min-heap of size k, or O(n) on average with quickselect.
Note: the tests include large already-sorted inputs and inputs where every value
is equal, so a quickselect needs a random pivot AND a partition that copes with
many equal values (e.g. a three-way partition).
*/
#include "prelude.hpp"

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        throw NotImplemented();
    }
};
