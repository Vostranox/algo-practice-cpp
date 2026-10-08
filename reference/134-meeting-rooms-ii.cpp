#include "prelude.hpp"

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> ends;
        for (auto& iv : intervals) {
            if (!ends.empty() && ends.top() <= iv[0]) {
                ends.pop();
            }
            ends.push(iv[1]);
        }
        return static_cast<int>(ends.size());
    }
};
