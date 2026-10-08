/*
5. Top K Frequent Elements  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/top-k-frequent-elements/

You get an integer array `nums` and an integer `k`. Return the `k` distinct
values that occur most often in `nums`, in any order.

The inputs guarantee that the answer is unique: the k-th highest frequency is
strictly greater than the (k+1)-th, so there is never a tie at the cut-off.

Example 1:
    Input:  nums = [4, 4, 4, 7, 7, 9], k = 2
    Output: [4, 7]        (4 occurs 3 times, 7 twice, 9 once)

Example 2:
    Input:  nums = [3, 0, 3, 0, 3, 5, 0, 0], k = 1
    Output: [0]           (0 occurs 4 times, 3 only 3 times)

Example 3:
    Input:  nums = [-1], k = 1
    Output: [-1]

Constraints:
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    1 <= k <= number of distinct values in nums
    the answer is unique

Target: better than O(n log n) — O(n) is possible (bucket by frequency).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        throw NotImplemented();
    }
};
