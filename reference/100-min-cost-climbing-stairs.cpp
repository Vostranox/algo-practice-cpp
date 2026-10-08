#include "prelude.hpp"

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int twoBack = 0, oneBack = 0;
        for (size_t i = 2; i <= cost.size(); ++i) {
            int cur = min(oneBack + cost[i - 1], twoBack + cost[i - 2]);
            twoBack = oneBack;
            oneBack = cur;
        }
        return oneBack;
    }
};
