#include "prelude.hpp"

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> price(n, INT_MAX);
        price[src] = 0;
        for (int round = 0; round <= k; ++round) {
            vector<int> next = price;
            for (auto& f : flights) {
                if (price[f[0]] != INT_MAX) {
                    next[f[1]] = min(next[f[1]], price[f[0]] + f[2]);
                }
            }
            price = move(next);
        }
        return price[dst] == INT_MAX ? -1 : price[dst];
    }
};
