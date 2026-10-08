/*
34. Median of Two Sorted Arrays  ·  Hard  ·  Binary Search
Source: https://leetcode.com/problems/median-of-two-sorted-arrays/

`nums1` (length m) and `nums2` (length n) are each sorted in non-decreasing
order. Either one may be empty, but not both. Return the median of all m + n
values taken together, as a double: the middle value when m + n is odd, or the
average of the two middle values when m + n is even.

The overall running time should be O(log(m + n)). (At these sizes the tests
can't tell that apart from an O(m + n) merge, so hold yourself to the target.)

Example 1:
    Input:  nums1 = [1, 4, 9], nums2 = [2, 3]
    Output: 3.0           (all values: 1, 2, 3, 4, 9)

Example 2:
    Input:  nums1 = [5, 6], nums2 = [1, 2, 10, 12]
    Output: 5.5           (all values: 1, 2, 5, 6, 10, 12 -> (5 + 6) / 2)

Example 3:
    Input:  nums1 = [], nums2 = [-3, -1]
    Output: -2.0

Constraints:
    0 <= m, n <= 1000
    1 <= m + n <= 2000
    -10^6 <= nums1[i], nums2[i] <= 10^6

Answers within 1e-5 are accepted.
*/
#include "prelude.hpp"

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        throw NotImplemented();
    }
};
