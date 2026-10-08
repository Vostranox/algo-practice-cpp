#include "prelude.hpp"

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (2 * k >= n) {
            int sum = 0;
            for (int i = 1; i < n; ++i) {
                sum += max(0, prices[i] - prices[i - 1]);
            }
            return sum;
        }
        vector<int> buy(k + 1, INT_MIN / 2), sell(k + 1, 0);
        for (int p : prices) {
            for (int j = 1; j <= k; ++j) {
                buy[j] = max(buy[j], sell[j - 1] - p);
                sell[j] = max(sell[j], buy[j] + p);
            }
        }
        return sell[k];
    }
};
