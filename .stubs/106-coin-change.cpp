/*
106. Coin Change  ·  Medium  ·  1-D Dynamic Programming
Source: https://leetcode.com/problems/coin-change/

`coins` lists the available coin values; you have an unlimited number of coins
of each value. Return the smallest number of coins whose values add up exactly
to `amount`, or -1 if no combination of coins makes that amount.
An amount of 0 needs 0 coins.

Example 1:
    Input:  coins = [1, 4, 6], amount = 8
    Output: 2          (4 + 4; always taking the biggest coin gives 6 + 1 + 1)

Example 2:
    Input:  coins = [5, 10], amount = 3
    Output: -1

Example 3:
    Input:  coins = [7], amount = 0
    Output: 0

Constraints:
    1 <= coins.length <= 12
    1 <= coins[i] <= 2^31 - 1
    0 <= amount <= 10^4

Target: O(amount * coins.length) time, O(amount) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        throw NotImplemented();
    }
};
