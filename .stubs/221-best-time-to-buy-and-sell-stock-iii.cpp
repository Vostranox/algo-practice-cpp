/*
221. Best Time to Buy and Sell Stock III  ·  Hard  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

`prices[i]` is the price of a stock on day i. You may make at most two
transactions, where a transaction is buying one share on some day and selling
it on a later day. You can hold at most one share at a time, so the second
purchase has to wait until the first share is sold. Return the maximum total
profit (0 if no transaction is worth making).

Example 1:
    Input:  prices = [2, 6, 1, 4, 3, 9]
    Output: 12      (buy at 2, sell at 6; buy at 1, sell at 9)

Example 2:
    Input:  prices = [3, 5, 7, 8]
    Output: 5       (one transaction is enough: buy at 3, sell at 8)

Example 3:
    Input:  prices = [9, 7, 4, 1]
    Output: 0

Constraints:
    1 <= prices.length <= 10^5
    0 <= prices[i] <= 10^5

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        throw NotImplemented();
    }
};
