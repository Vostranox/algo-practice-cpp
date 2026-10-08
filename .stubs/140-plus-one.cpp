/*
140. Plus One  ·  Easy  ·  Math & Geometry
Source: https://leetcode.com/problems/plus-one/

A non-negative integer is stored as an array of its decimal digits, most
significant digit first (so 307 is [3, 0, 7]). There are no leading zeros,
except that the number 0 itself is [0].

Return the digits of that number plus one, in the same format (returning a
new vector or the modified input are both fine).

Example 1:
    Input:  digits = [4, 5, 9]
    Output: [4, 6, 0]

Example 2:
    Input:  digits = [9, 9]
    Output: [1, 0, 0]       (the answer can be one digit longer)

Example 3:
    Input:  digits = [0]
    Output: [1]

Constraints:
    1 <= digits.length <= 100
    0 <= digits[i] <= 9
    no leading zeros (except for the number 0, given as [0])

Target: O(n) time. A 100-digit number doesn't fit in any built-in integer
type, so work on the digits directly.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        throw NotImplemented();
    }
};
