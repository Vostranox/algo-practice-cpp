#include "prelude.hpp"

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        vector<pair<int, int>> iv;
        iv.reserve(intervals.size());
        for (auto& v : intervals) {
            iv.emplace_back(v[1], v[0]);
        }
        sort(iv.begin(), iv.end());
        int removed = 0;
        int64_t prev_end = INT64_MIN;
        for (auto [end, start] : iv) {
            if (start >= prev_end) {
                prev_end = end;
            } else {
                ++removed;
            }
        }
        return removed;
    }
};
