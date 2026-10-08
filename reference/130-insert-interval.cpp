#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int start = newInterval[0], end = newInterval[1];
        size_t i = 0, n = intervals.size();
        while (i < n && intervals[i][1] < start) {
            res.push_back(intervals[i++]);
        }
        while (i < n && intervals[i][0] <= end) {
            start = min(start, intervals[i][0]);
            end = max(end, intervals[i][1]);
            ++i;
        }
        res.push_back({start, end});
        while (i < n) {
            res.push_back(intervals[i++]);
        }
        return res;
    }
};
