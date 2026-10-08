#include "prelude.hpp"

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<uint64_t> ways(amount + 1, 0);
        ways[0] = 1;
        for (int c : coins) {
            for (int a = c; a <= amount; ++a) {
                ways[a] += ways[a - c];
            }
        }
        return static_cast<int>(ways[amount]);
    }
};
