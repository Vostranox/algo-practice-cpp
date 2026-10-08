#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;

static void run(Grid matrix, int want) {
    Grid arg = matrix;
    check(Solution().longestIncreasingPath(arg), want, "matrix", matrix);
}

static const int DR[] = {1, -1, 0, 0}, DC[] = {0, 0, 1, -1};

static int walk(const Grid& g, int r, int c) {
    int best = 1;
    for (int d = 0; d < 4; ++d) {
        int nr = r + DR[d], nc = c + DC[d];
        if (nr >= 0 && nr < static_cast<int>(g.size()) && nc >= 0 && nc < static_cast<int>(g[0].size()) && g[nr][nc] > g[r][c]) {
            best = max(best, 1 + walk(g, nr, nc));
        }
    }
    return best;
}

static int brute(const Grid& g) {
    int best = 0;
    for (int r = 0; r < static_cast<int>(g.size()); ++r) {
        for (int c = 0; c < static_cast<int>(g[0].size()); ++c) {
            best = max(best, walk(g, r, c));
        }
    }
    return best;
}

static int layers(const Grid& g) {
    int m = g.size(), n = g[0].size(), count = 0;
    vector<vector<int>> indeg(m, vector<int>(n, 0));
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            for (int d = 0; d < 4; ++d) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && g[nr][nc] < g[r][c]) {
                    ++indeg[r][c];
                }
            }
        }
    }
    vector<pair<int, int>> layer;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (!indeg[r][c]) {
                layer.push_back({r, c});
            }
        }
    }
    while (!layer.empty()) {
        ++count;
        vector<pair<int, int>> next;
        for (auto [r, c] : layer) {
            for (int d = 0; d < 4; ++d) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && g[nr][nc] > g[r][c] && --indeg[nr][nc] == 0) {
                    next.push_back({nr, nc});
                }
            }
        }
        layer = move(next);
    }
    return count;
}

TEST(examples) {
    run({{1, 2, 3}, {6, 5, 4}, {7, 8, 9}}, 9);
    run({{9, 1}, {3, 2}}, 4);
    run({{5, 5}, {5, 5}}, 1);
}

TEST(edge_cases) {
    run({{7}}, 1);
    run({{1, 2}}, 2);
    run({{2}, {1}}, 2);
    run({{1, 3, 2, 4, 5}}, 3);
    run({{0, INT_MAX}}, 2);
    run({{3, 4, 5}, {3, 2, 6}, {2, 2, 1}}, 4);
    run({{1, 1, 1}, {1, 2, 1}, {1, 1, 1}}, 2);
    run({{2, 1}, {1, 2}}, 2);
}

TEST(random) {
    Rng rng(1170);
    for (int iter = 0; iter < 300; ++iter) {
        int m = rng(1, 4), n = rng(1, 5), hi = rng(0, 12);
        Grid g(m);
        for (auto& row : g) {
            row = rng.ints(n, 0, hi);
        }
        run(g, brute(g));
    }
}

TEST(large) {
    const int N = 200;
    Grid g(N, vector<int>(N));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            g[r][c] = r + c;
        }
    }
    run(g, 2 * N - 1);
    run(Grid(N, vector<int>(N, INT_MAX)), 1);
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            g[r][c] = r * N + (r % 2 ? N - 1 - c : c);
        }
    }
    run(g, N * N);
    Rng rng(1171);
    for (int hi : {3, 1000, INT_MAX}) {
        for (auto& row : g) {
            row = rng.ints(N, 0, hi);
        }
        run(g, layers(g));
    }
}

}
