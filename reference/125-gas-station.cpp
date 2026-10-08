#include "prelude.hpp"

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0, tank = 0, start = 0;
        for (int i = 0; i < static_cast<int>(gas.size()); ++i) {
            total += gas[i] - cost[i];
            tank += gas[i] - cost[i];
            if (tank < 0) {
                tank = 0;
                start = i + 1;
            }
        }
        return total < 0 ? -1 : start;
    }
};
