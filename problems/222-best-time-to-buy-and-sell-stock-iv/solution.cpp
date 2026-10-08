/*
222. Best Time to Buy and Sell Stock IV  ·  Hard  ·  2-D Dynamic Programming
Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

`prices[i]` is the price of a stock on day i. You may make at most `k`
transactions, where a transaction is buying one share on some day and selling
it on a later day. You can hold at most one share at a time, so each purchase
has to wait until the previous share is sold. Return the maximum total profit
(0 if no transaction is worth making).

Example 1:
    Input:  k = 2, prices = [3, 1, 4, 1, 5, 9, 2, 6]
    Output: 12      (buy at 1, sell at 9; buy at 2, sell at 6)

Example 2:
    Input:  k = 3, prices = [3, 1, 4, 1, 5, 9, 2, 6]
    Output: 15      (1 -> 4, 1 -> 9, 2 -> 6)

Example 3:
    Input:  k = 100, prices = [1, 3, 2, 8]
    Output: 8       (k is more than enough: take both rises, 1 -> 3 and 2 -> 8)

Constraints:
    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000

Target: O(n * k) time, O(k) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        throw NotImplemented();
    }
};
