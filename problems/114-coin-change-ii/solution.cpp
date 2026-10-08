/*
114. Coin Change II  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/coin-change-ii/

`coins` lists distinct coin values, with an unlimited number of coins of each
value. Return the number of different combinations of coins that add up
exactly to `amount`. Order does not matter: 1+2 and 2+1 are the same
combination. Return 0 if no combination works; for amount 0 the answer is 1
(the empty combination).

Example 1:
    Input:  amount = 6, coins = [1, 3, 4]
    Output: 4          (1+1+1+1+1+1, 3+1+1+1, 3+3, 4+1+1)

Example 2:
    Input:  amount = 7, coins = [2, 4]
    Output: 0

Example 3:
    Input:  amount = 0, coins = [5]
    Output: 1

Constraints:
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000, all values distinct
    0 <= amount <= 5000
    the answer fits in a 32-bit signed integer (the counts for smaller amounts
    may be far larger, so watch out for overflow in intermediate values)

Target: O(amount * coins.length) time, O(amount) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        throw NotImplemented();
    }
};
