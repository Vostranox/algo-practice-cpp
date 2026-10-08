#include "prelude.hpp"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int hold = INT_MIN / 2, sold = 0, rest = 0;
        for (int p : prices) {
            int newHold = max(hold, rest - p);
            int newSold = hold + p;
            rest = max(rest, sold);
            hold = newHold;
            sold = newSold;
        }
        return max(sold, rest);
    }
};
