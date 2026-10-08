#include "prelude.hpp"

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<pair<int, int>> iv;
        iv.reserve(intervals.size());
        for (auto& v : intervals) {
            iv.emplace_back(v[0], v[1]);
        }
        sort(iv.begin(), iv.end());
        vector<int> order(queries.size()), answer(queries.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) { return queries[a] < queries[b]; });
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> heap;
        size_t i = 0;
        for (int idx : order) {
            int q = queries[idx];
            for (; i < iv.size() && iv[i].first <= q; ++i) {
                heap.push({iv[i].second - iv[i].first + 1, iv[i].second});
            }
            while (!heap.empty() && heap.top().second < q) {
                heap.pop();
            }
            answer[idx] = heap.empty() ? -1 : heap.top().first;
        }
        return answer;
    }
};
