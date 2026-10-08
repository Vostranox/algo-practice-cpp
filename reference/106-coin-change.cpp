#include "prelude.hpp"

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        const int INF = amount + 1;
        vector<int> fewest(amount + 1, INF);
        fewest[0] = 0;
        for (int a = 1; a <= amount; ++a) {
            for (int c : coins) {
                if (c <= a) {
                    fewest[a] = min(fewest[a], fewest[a - c] + 1);
                }
            }
        }
        return fewest[amount] == INF ? -1 : fewest[amount];
    }
};
