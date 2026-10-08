#include "prelude.hpp"

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0), st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && temperatures[st.back()] < temperatures[i]) {
                answer[st.back()] = i - st.back();
                st.pop_back();
            }
            st.push_back(i);
        }
        return answer;
    }
};
