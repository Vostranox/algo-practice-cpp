/*
139. Happy Number  ·  Easy  ·  Math & Geometry
Source: https://leetcode.com/problems/happy-number/

Take a positive integer n and repeatedly replace it with the sum of the
squares of its decimal digits. If this process eventually reaches 1 (where it
stays, since 1^2 = 1), n is called happy. Otherwise the sequence never reaches
1 and instead loops forever around a cycle of other numbers.

Return true if n is happy and false otherwise.

Example 1:
    Input:  n = 7
    Output: true      (7 -> 49 -> 97 -> 130 -> 10 -> 1)

Example 2:
    Input:  n = 4
    Output: false     (4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4 -> ... repeats)

Example 3:
    Input:  n = 100
    Output: true      (1^2 + 0^2 + 0^2 = 1)

Constraints:
    1 <= n <= 2^31 - 1

Follow-up: detecting the loop with a set of seen numbers is easy; can you do
it with O(1) extra memory?
*/
#include "prelude.hpp"

class Solution {
public:
    bool isHappy(int n) {
        throw NotImplemented();
    }
};
