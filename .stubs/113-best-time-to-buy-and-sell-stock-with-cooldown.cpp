/*
113. Best Time to Buy and Sell Stock with Cooldown  ·  Medium  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

`prices[i]` is the price of a stock on day i. You may trade as often as you
like, under these rules:
  - you hold at most one share at a time (sell before you buy again);
  - each day you can do at most one thing: buy, sell, or nothing;
  - the day right after a sale is a cooldown day: you can't buy on it.
Return the maximum total profit (0 if no trade is worth making).

Example 1:
    Input:  prices = [3, 8, 1, 6]
    Output: 5          (buy at 3, sell at 8; day 2 is a cooldown, so 1 -> 6 can't follow.
                        Buying at 1 and selling at 6 alone also gives 5.)

Example 2:
    Input:  prices = [1, 4, 2, 7]
    Output: 6          (buy at 1, sell at 7)

Example 3:
    Input:  prices = [7, 5, 3]
    Output: 0

Constraints:
    1 <= prices.length <= 5000
    0 <= prices[i] <= 1000

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        throw NotImplemented();
    }
};
