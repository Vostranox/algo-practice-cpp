#include "prelude.hpp"

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), best = 1;
        for (int i = 0; i < n; ++i) {
            unordered_map<int, int> count;
            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0], dy = points[j][1] - points[i][1];
                int g = gcd(dx, dy);
                dx /= g, dy /= g;
                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx, dy = -dy;
                }
                best = max(best, ++count[dx * 40001 + dy + 20000] + 1);
            }
        }
        return best;
    }
};
