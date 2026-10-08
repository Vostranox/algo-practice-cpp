#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, int>> heap;
        for (int i = 0; i < static_cast<int>(points.size()); ++i) {
            int d = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            heap.emplace(d, i);
            if (static_cast<int>(heap.size()) > k) {
                heap.pop();
            }
        }
        vector<vector<int>> res;
        for (; !heap.empty(); heap.pop()) {
            res.push_back(points[heap.top().second]);
        }
        return res;
    }
};
