#include "prelude.hpp"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int cheapest = prices[0], best = 0;
        for (int p : prices) {
            cheapest = min(cheapest, p);
            best = max(best, p - cheapest);
        }
        return best;
    }
};
