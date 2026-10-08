/*
74. Subsets II  ·  Medium  ·  Backtracking
Source: https://leetcode.com/problems/subsets-ii/

Like Subsets, but `nums` may contain repeated values. Return every distinct
subset: two subsets are the same if they contain the same values the same number
of times, no matter the order or which copy of a repeated value was picked. For
nums = [3, 3] the answer is [[], [3], [3, 3]] -- [3] must appear only once.

Return the subsets in any order; the numbers inside a subset may also be in any
order. The empty subset is always included.

Example 1:
    Input:  nums = [2, 5, 2]
    Output: [[], [2], [5], [2, 2], [2, 5], [2, 2, 5]]

Example 2:
    Input:  nums = [7]
    Output: [[], [7]]

Example 3:
    Input:  nums = [1, 1, 1]
    Output: [[], [1], [1, 1], [1, 1, 1]]

Constraints:
    1 <= nums.length <= 10
    -10 <= nums[i] <= 10

Target: O(n * 2^n). Generate each distinct subset once -- sort nums, and when
you decide to skip a value, skip all its copies -- rather than generating
duplicates and filtering them out afterwards.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        throw NotImplemented();
    }
};
