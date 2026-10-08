#include "prelude.hpp"

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        const int INF = INT_MAX, rows = rooms.size(), cols = rooms[0].size();
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        queue<pair<int, int>> q;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (rooms[r][c] == 0) {
                    q.push({r, c});
                }
            }
        }
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int x = r + dr[d], y = c + dc[d];
                if (x >= 0 && x < rows && y >= 0 && y < cols && rooms[x][y] == INF) {
                    rooms[x][y] = rooms[r][c] + 1;
                    q.push({x, y});
                }
            }
        }
    }
};
