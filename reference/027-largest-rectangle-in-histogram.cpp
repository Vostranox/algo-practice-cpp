#include "prelude.hpp"

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size(), best = 0;
        vector<pair<int, int>> st;
        for (int i = 0; i < n; ++i) {
            int start = i;
            while (!st.empty() && st.back().second > heights[i]) {
                auto [j, h] = st.back();
                st.pop_back();
                best = max(best, h * (i - j));
                start = j;
            }
            st.push_back({start, heights[i]});
        }
        for (auto [j, h] : st) {
            best = max(best, h * (n - j));
        }
        return best;
    }
};
