#include "prelude.hpp"

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid[0].size();
        vector<int> row(n, 0);
        row[0] = 1;
        for (auto& cells : obstacleGrid) {
            for (int c = 0; c < n; ++c) {
                if (cells[c]) {
                    row[c] = 0;
                } else if (c > 0) {
                    row[c] += row[c - 1];
                }
            }
        }
        return row[n - 1];
    }
};
