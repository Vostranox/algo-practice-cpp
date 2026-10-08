#include "prelude.hpp"

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) { return position[a] > position[b]; });
        vector<double> st;
        for (int i : order) {
            double t = double(target - position[i]) / speed[i];
            if (st.empty() || t > st.back()) {
                st.push_back(t);
            }
        }
        return static_cast<int>(st.size());
    }
};
