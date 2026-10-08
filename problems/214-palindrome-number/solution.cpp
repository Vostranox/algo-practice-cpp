/*
214. Palindrome Number  ·  Easy  ·  Math & Geometry
Source: https://leetcode.com/problems/palindrome-number/

Given a 32-bit signed integer x, return true if its decimal digits read the
same from left to right as from right to left, and false otherwise. A negative
number is never a palindrome: "-121" read backwards is "121-".

Example 1:
    Input:  x = 1331
    Output: true

Example 2:
    Input:  x = -44
    Output: false     (backwards it reads "44-")

Example 3:
    Input:  x = 120
    Output: false     (backwards it reads "021")

Constraints:
    -2^31 <= x <= 2^31 - 1

Follow-up: solve it without turning x into a string (honor system: the tests
can't tell). Careful: reversing all the digits of a 10-digit int can exceed
2^31 - 1; signed overflow is undefined behaviour and crashes under the tests'
sanitizers.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isPalindrome(int x) {
        throw NotImplemented();
    }
};
