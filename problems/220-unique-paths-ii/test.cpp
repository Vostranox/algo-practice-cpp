#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;
using Table = vector<vector<int64_t>>;

const int64_t LIMIT = 2000000000;

static Table from_start(const Grid& g) {
    int m = g.size(), n = g[0].size();
    Table f(m, vector<int64_t>(n, 0));
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (!g[r][c]) {
                f[r][c] = r == 0 && c == 0 ? 1 : min(LIMIT + 1, (r ? f[r - 1][c] : 0) + (c ? f[r][c - 1] : 0));
            }
        }
    }
    return f;
}

static Table to_target(const Grid& g) {
    int m = g.size(), n = g[0].size();
    Table b(m, vector<int64_t>(n, 0));
    for (int r = m - 1; r >= 0; --r) {
        for (int c = n - 1; c >= 0; --c) {
            if (!g[r][c]) {
                b[r][c] = r == m - 1 && c == n - 1 ? 1
                                                   : min(LIMIT + 1, (r + 1 < m ? b[r + 1][c] : 0) + (c + 1 < n ? b[r][c + 1] : 0));
            }
        }
    }
    return b;
}

static bool fits(const Grid& g) {
    int m = g.size(), n = g[0].size();
    Table f = from_start(g), b = to_target(g);
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if ((r ? f[r - 1][c] : 0) + (c ? f[r][c - 1] : 0) > LIMIT) return false;
            if ((r + 1 < m ? b[r + 1][c] : 0) + (c + 1 < n ? b[r][c + 1] : 0) > LIMIT) return false;
        }
    }
    return true;
}

static void run(const Grid& grid, int want) {
    if (!fits(grid)) {
        fail("broken test: grid exceeds the promised bound");
    }
    Grid arg = grid;
    check(Solution().uniquePathsWithObstacles(arg), want, "obstacleGrid", grid);
}

static void run(const Grid& grid) { run(grid, static_cast<int>(to_target(grid)[0][0])); }

static int every_route(const Grid& g, int r = 0, int c = 0) {
    int m = g.size(), n = g[0].size();
    if (g[r][c]) return 0;
    if (r == m - 1 && c == n - 1) return 1;
    return (r + 1 < m ? every_route(g, r + 1, c) : 0) + (c + 1 < n ? every_route(g, r, c + 1) : 0);
}

static Grid random_grid(Rng& rng, int m, int n, double density) {
    Grid g(m, vector<int>(n, 0));
    for (auto& row : g) {
        for (int& x : row) {
            x = rng.coin(density);
        }
    }
    if (rng.coin(0.8)) {
        g[0][0] = g[m - 1][n - 1] = 0;
    }
    return g;
}

static Grid carved(Rng& rng) {
    Grid g(100, vector<int>(100, 1));
    vector<pair<int, int>> corridor;
    for (int r = 0, c = 0;;) {
        g[r][c] = 0;
        corridor.push_back({r, c});
        if (r == 99 && c == 99) break;
        if (c == 99 || (r < 99 && rng.coin())) {
            ++r;
        } else {
            ++c;
        }
    }
    for (int k = rng(2, 8); k > 0; --k) {
        int h = rng(2, 14), w = rng(2, 14), r0 = rng(0, 100 - h), c0 = rng(0, 100 - w);
        if (rng.coin(0.7)) {
            auto [r, c] = rng.pick(corridor);
            r0 = clamp(r - rng(0, h - 1), 0, 100 - h), c0 = clamp(c - rng(0, w - 1), 0, 100 - w);
        }
        for (int r = r0; r < r0 + h; ++r) {
            for (int c = c0; c < c0 + w; ++c) {
                g[r][c] = rng.coin(0.1);
            }
        }
    }
    g[0][0] = g[99][99] = 0;
    return g;
}

TEST(examples) {
    run({{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, 4);
    run({{0, 1}, {1, 0}}, 0);
    run({{0, 0, 0, 0, 0}}, 1);
}

TEST(edge_cases) {
    run({{0}}, 1);
    run({{1}}, 0);
    run({{1, 0}, {0, 0}}, 0);
    run({{0, 0}, {0, 1}}, 0);
    run({{0}, {1}, {0}}, 0);
    run({{0, 1, 0}}, 0);
    run({{0, 1, 0}, {0, 0, 0}}, 1);
    run({{0, 0}, {1, 0}, {0, 0}}, 1);
    run({{0, 0}, {1, 1}, {0, 0}}, 0);
    run({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 6);
    run({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}, 2);
    run({{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, 2);
}

TEST(random) {
    Rng rng(630);
    for (int iter = 0; iter < 400; ++iter) {
        Grid g = random_grid(rng, rng(1, 7), rng(1, 7), rng.pick(vector<double>{0.0, 0.1, 0.3}));
        run(g, every_route(g));
    }
    for (int done = 0; done < 100;) {
        Grid g = random_grid(rng, rng(1, 30), rng(1, 30), rng.pick(vector<double>{0.15, 0.25, 0.35}));
        if (!fits(g)) continue;
        run(g);
        ++done;
    }
}

TEST(large) {
    run(Grid(17, vector<int>(18, 0)), 1166803110);
    run(Grid(18, vector<int>(17, 0)), 1166803110);
    run(Grid(1, vector<int>(100, 0)), 1);
    run(Grid(100, vector<int>(1, 0)), 1);
    Grid g(100, vector<int>(100, 1));
    for (int c = 0; c <= 40; ++c) {
        g[0][c] = 0;
    }
    for (int r = 0; r < 30; ++r) {
        g[r][40] = 0;
    }
    for (int r = 30; r < 46; ++r) {
        for (int c = 40; c < 60; ++c) {
            g[r][c] = 0;
        }
    }
    for (int r = 46; r < 100; ++r) {
        g[r][59] = 0;
    }
    for (int c = 59; c < 100; ++c) {
        g[99][c] = 0;
    }
    run(g, 1855967520);
    g[0][0] = 1;
    run(g, 0);
    g[0][0] = 0, g[99][99] = 1;
    run(g, 0);
    g[99][99] = 0, g[38][50] = 1;
    run(g);
    Rng rng(631);
    for (int done = 0; done < 6;) {
        g = carved(rng);
        int64_t want = to_target(g)[0][0];
        if (want < 1000000 || !fits(g)) continue;
        run(g, static_cast<int>(want));
        ++done;
    }
}

}
