#include "prelude.hpp"

class Solution {
    vector<vector<int>> memo;

    int longest(const vector<vector<int>>& g, int r, int c) {
        if (memo[r][c]) return memo[r][c];
        static const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        int best = 1;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < static_cast<int>(g.size()) && nc >= 0 && nc < static_cast<int>(g[0].size()) && g[nr][nc] > g[r][c]) {
                best = max(best, 1 + longest(g, nr, nc));
            }
        }
        return memo[r][c] = best;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), best = 0;
        memo.assign(m, vector<int>(n, 0));
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                best = max(best, longest(matrix, r, c));
            }
        }
        return best;
    }
};
