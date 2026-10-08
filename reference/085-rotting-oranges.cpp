#include "prelude.hpp"

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size(), fresh = 0, minutes = 0;
        queue<pair<int, int>> q;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                }
                fresh += grid[r][c] == 1;
            }
        }
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!q.empty() && fresh > 0) {
            for (int k = q.size(); k > 0; --k) {
                auto [r, c] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d) {
                    int x = r + dr[d], y = c + dc[d];
                    if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
                        grid[x][y] = 2;
                        --fresh;
                        q.push({x, y});
                    }
                }
            }
            ++minutes;
        }
        return fresh == 0 ? minutes : -1;
    }
};
