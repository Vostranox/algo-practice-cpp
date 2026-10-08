#include "prelude.hpp"

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> best(n, INT_MAX);
        best[0] = 0;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                best[c] = grid[r][c] + (c == 0 ? best[0] : min(best[c], best[c - 1]));
            }
        }
        return best[n - 1];
    }
};
