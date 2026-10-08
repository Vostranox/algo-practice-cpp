/*
210. Find K Pairs with Smallest Sums  ·  Medium  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/

You get two integer arrays nums1 and nums2, each sorted in non-decreasing order,
and an integer k. A pair is formed by choosing a position i in nums1 and a
position j in nums2; it is written [nums1[i], nums2[j]] and its sum is
nums1[i] + nums2[j]. There are nums1.length * nums2.length pairs, one for each
choice of (i, j). Return k of them whose sums are the smallest.

When sums tie, several answers can be right, and any of them is accepted.
Precisely: the k returned pairs must come from k different choices of (i, j),
and their sums must be, as a multiset, the k smallest of all the sums. Return
the pairs in any order. Repeated values in the arrays mean the same [u, v] can
legitimately appear more than once (as often as there are positions holding u
in nums1 times positions holding v in nums2), but never more often than that.

Example 1:
    Input:  nums1 = [1, 4, 9], nums2 = [2, 3, 8], k = 4
    Output: [[1, 2], [1, 3], [4, 2], [4, 3]]    (sums 3, 4, 6, 7)

Example 2:
    Input:  nums1 = [2, 2, 5], nums2 = [0, 6], k = 3
    Output: [[2, 0], [2, 0], [5, 0]]    (nums1 has two 2s, so [2, 0] twice)

Example 3:
    Input:  nums1 = [0, 1], nums2 = [1, 2], k = 2
    Output: [[0, 1], [0, 2]]  or  [[0, 1], [1, 1]]
            (the sums are 1, 2, 2, 3: the second-smallest sum, 2, is a tie)

Constraints:
    1 <= nums1.length, nums2.length <= 10^5
    -10^9 <= nums1[i], nums2[j] <= 10^9
    nums1 and nums2 are sorted in non-decreasing order
    1 <= k <= 10^4
    k <= nums1.length * nums2.length

Target: O(k log k) with a min-heap of candidate pairs. (The large tests have
10^5 elements per array: building all the pairs, or even all k * k pairs from
the first k elements of each, is too slow.)
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        throw NotImplemented();
    }
};
