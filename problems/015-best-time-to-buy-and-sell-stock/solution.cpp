/*
15. Best Time to Buy and Sell Stock  ·  Easy  ·  Sliding Window
Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

You get an array `prices` where prices[i] is a stock's price on day i. You may
buy one share on one day and sell it on a strictly later day. Return the
largest profit (sell price - buy price) you can make. If no trade makes a
profit, return 0 (you simply don't trade).

Example 1:
    Input:  prices = [8, 3, 6, 1, 5, 4]
    Output: 4             (buy at 1 on day 3, sell at 5 on day 4)

Example 2:
    Input:  prices = [9, 7, 4, 2]
    Output: 0             (prices only fall)

Example 3:
    Input:  prices = [4, 9, 1, 3]
    Output: 5             (the lowest price 1 comes after the highest price 9)

Constraints:
    1 <= prices.length <= 10^5
    0 <= prices[i] <= 10^4

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        throw NotImplemented();
    }
};
