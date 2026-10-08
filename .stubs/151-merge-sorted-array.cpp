/*
151. Merge Sorted Array  ·  Easy  ·  Two Pointers
Source: https://leetcode.com/problems/merge-sorted-array/

You get two integer arrays, each sorted in non-decreasing order. `nums2` holds
n values. `nums1` has room for m + n values: its first m entries are real
values, and its last n entries are zeros that only reserve space.

Merge `nums2` into `nums1` in place, so that afterwards `nums1` holds all
m + n values in non-decreasing order. The function returns nothing; the result
is read from `nums1`.

Example 1:
    Input:  nums1 = [2, 5, 9, 0, 0], m = 3, nums2 = [4, 10], n = 2
    After:  nums1 = [2, 4, 5, 9, 10]

Example 2:
    Input:  nums1 = [0, 0, 0], m = 0, nums2 = [-3, 1, 1], n = 3
    After:  nums1 = [-3, 1, 1]       (nums1 had no real values yet)

Example 3:
    Input:  nums1 = [7], m = 1, nums2 = [], n = 0
    After:  nums1 = [7]

Constraints:
    nums1.length == m + n,  nums2.length == n
    0 <= m, n <= 200,  1 <= m + n <= 200
    -10^9 <= nums1[i], nums2[j] <= 10^9

Target: O(m + n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        throw NotImplemented();
    }
};
