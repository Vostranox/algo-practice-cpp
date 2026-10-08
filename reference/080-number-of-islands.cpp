#include "prelude.hpp"

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size(), cols = grid[0].size(), islands = 0;
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] != '1') continue;
                ++islands;
                grid[r][c] = '0';
                vector<pair<int, int>> stack{{r, c}};
                while (!stack.empty()) {
                    auto [i, j] = stack.back();
                    stack.pop_back();
                    for (int d = 0; d < 4; ++d) {
                        int x = i + dr[d], y = j + dc[d];
                        if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '1') {
                            grid[x][y] = '0';
                            stack.push_back({x, y});
                        }
                    }
                }
            }
        }
        return islands;
    }
};
