#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;

static void run(const Grid& grid, int want) {
    Grid arg = grid;
    check(Solution().orangesRotting(arg), want, "grid", grid);
}

static int simulate(Grid g) {
    int m = g.size(), n = g[0].size(), minutes = 0;
    auto any_fresh = [&] {
        for (auto& row : g) {
            for (int x : row) {
                if (x == 1) return true;
            }
        }
        return false;
    };
    while (any_fresh()) {
        vector<pair<int, int>> newly;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (g[r][c] != 1) continue;
                bool touches = (r > 0 && g[r - 1][c] == 2) || (r + 1 < m && g[r + 1][c] == 2) ||
                               (c > 0 && g[r][c - 1] == 2) || (c + 1 < n && g[r][c + 1] == 2);
                if (touches) {
                    newly.push_back({r, c});
                }
            }
        }
        if (newly.empty()) return -1;
        for (auto [r, c] : newly) {
            g[r][c] = 2;
        }
        ++minutes;
    }
    return minutes;
}

TEST(examples) {
    run({{2, 1, 1}, {0, 0, 1}, {1, 1, 1}}, 6);
    run({{1, 0, 2}}, -1);
    run({{0, 2}}, 0);
}

TEST(edge_cases) {
    run({{1}}, -1);
    run({{2}}, 0);
    run({{0}}, 0);
    run({{1, 1}, {1, 1}}, -1);
    run({{2, 1, 1, 1, 2}}, 2);
    run({{2, 1, 1}, {1, 1, 1}, {1, 1, 2}}, 2);
    run({{2, 0, 1}}, -1);
    run({{2}, {1}, {1}, {0}, {2}}, 2);
    run({{1, 2, 1}, {0, 1, 0}, {1, 1, 1}}, 3);
}

TEST(random) {
    Rng rng(85);
    for (int t = 0; t < 500; ++t) {
        int m = rng(1, 10), n = rng(1, 10);
        double empty = rng.real(), fresh = 3 * rng.real(), rotten = 0.3 * rng.real();
        Grid g(m, vector<int>(n));
        for (auto& row : g) {
            for (int& x : row) {
                double u = rng.real() * (empty + fresh + rotten);
                x = u < empty ? 0 : u < empty + fresh ? 1 : 2;
            }
        }
        run(g, simulate(g));
    }
}

TEST(largest_grids) {
    const int n = 10;
    Grid g(n, vector<int>(n, 1));
    g[0][0] = 2;
    run(g, 18);
    g.assign(n, vector<int>(n, 1));
    g[4][4] = 2;
    run(g, 10);
    for (int r = 0; r < n; ++r) {
        g[r].assign(n, r % 2 == 0 ? 1 : 0);
    }
    for (int r = 1; r < n; r += 2) {
        g[r][(r / 2) % 2 == 0 ? n - 1 : 0] = 1;
    }
    g[0][0] = 2;
    run(g, 54);
    g[5][9] = 0;
    run(g, -1);
}

}
