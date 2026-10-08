#include "prelude.hpp"

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        vector<vector<bool>> seen(n, vector<bool>(n, false));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> heap;
        heap.push({grid[0][0], 0, 0});
        seen[0][0] = true;
        while (true) {
            auto [t, r, c] = heap.top();
            heap.pop();
            if (r == n - 1 && c == n - 1) return t;
            for (int d = 0; d < 4; ++d) {
                int x = r + dr[d], y = c + dc[d];
                if (x >= 0 && x < n && y >= 0 && y < n && !seen[x][y]) {
                    seen[x][y] = true;
                    heap.push({max(t, grid[x][y]), x, y});
                }
            }
        }
    }
};
