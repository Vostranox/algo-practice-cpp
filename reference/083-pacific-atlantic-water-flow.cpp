#include "prelude.hpp"

class Solution {
    int rows = 0, cols = 0;

    vector<vector<bool>> reach(const vector<vector<int>>& h, vector<pair<int, int>> stack) {
        vector<vector<bool>> seen(rows, vector<bool>(cols));
        for (auto [r, c] : stack) {
            seen[r][c] = true;
        }
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!stack.empty()) {
            auto [r, c] = stack.back();
            stack.pop_back();
            for (int d = 0; d < 4; ++d) {
                int x = r + dr[d], y = c + dc[d];
                if (x >= 0 && x < rows && y >= 0 && y < cols && !seen[x][y] && h[x][y] >= h[r][c]) {
                    seen[x][y] = true;
                    stack.push_back({x, y});
                }
            }
        }
        return seen;
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        rows = heights.size(), cols = heights[0].size();
        vector<pair<int, int>> pac, atl;
        for (int c = 0; c < cols; ++c) {
            pac.push_back({0, c}), atl.push_back({rows - 1, c});
        }
        for (int r = 0; r < rows; ++r) {
            pac.push_back({r, 0}), atl.push_back({r, cols - 1});
        }
        auto p = reach(heights, pac), a = reach(heights, atl);
        vector<vector<int>> out;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (p[r][c] && a[r][c]) {
                    out.push_back({r, c});
                }
            }
        }
        return out;
    }
};
