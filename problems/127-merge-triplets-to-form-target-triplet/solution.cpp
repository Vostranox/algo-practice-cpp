/*
127. Merge Triplets to Form Target Triplet  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/merge-triplets-to-form-target-triplet/

A triplet is an array of three integers. You get an array `triplets` and a
triplet `target`. You may apply the following operation as many times as you
like (including zero times):

    pick two different indices i and j and overwrite triplets[j] with the
    element-wise maximum of the two:
        [max(a_i, a_j), max(b_i, b_j), max(c_i, c_j)]

Return true if you can make `target` appear as one of the triplets in the
array, otherwise false.

Example 1:
    Input:  triplets = [[1, 4, 2], [3, 1, 5], [2, 3, 6]], target = [3, 4, 5]
    Output: true
            Merging [1, 4, 2] into [3, 1, 5] gives [3, 4, 5]. The last triplet
            can never be used: its 6 would push the third value past 5.

Example 2:
    Input:  triplets = [[4, 1, 1], [1, 2, 6]], target = [4, 2, 5]
    Output: false         (no usable way to get a 5 in the third position)

Example 3:
    Input:  triplets = [[5, 5, 5]], target = [5, 5, 5]
    Output: true          (already there, zero operations)

Constraints:
    1 <= triplets.length <= 10^5
    triplets[i].length == target.length == 3
    1 <= every value in triplets and target <= 1000

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        throw NotImplemented();
    }
};
