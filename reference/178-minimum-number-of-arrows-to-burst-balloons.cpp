#include "prelude.hpp"

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](const auto& a, const auto& b) { return a[1] < b[1]; });
        int arrows = 1;
        int x = points[0][1];
        for (const auto& p : points) {
            if (p[0] > x) {
                ++arrows;
                x = p[1];
            }
        }
        return arrows;
    }
};
