#include "prelude.hpp"

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) { return capital[a] < capital[b]; });
        priority_queue<int> available;
        for (int i = 0; k > 0; --k) {
            while (i < n && capital[order[i]] <= w) {
                available.push(profits[order[i++]]);
            }
            if (available.empty()) break;
            w += available.top();
            available.pop();
        }
        return w;
    }
};
