#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;

static void run(const Grid& grid, int want) {
    Grid arg = grid;
    check(Solution().maxAreaOfIsland(arg), want, "grid", grid);
}

static int largest_island(const Grid& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> label(m, vector<int>(n, -1));
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (g[r][c] == 1) {
                label[r][c] = r * n + c;
            }
        }
    }
    for (bool changed = true; changed;) {
        changed = false;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (label[r][c] < 0) continue;
                int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int x = r + dr[d], y = c + dc[d];
                    if (x >= 0 && x < m && y >= 0 && y < n && label[x][y] >= 0 && label[x][y] < label[r][c]) {
                        label[r][c] = label[x][y];
                        changed = true;
                    }
                }
            }
        }
    }
    map<int, int> size;
    int best = 0;
    for (auto& row : label) {
        for (int v : row) {
            if (v >= 0) {
                best = max(best, ++size[v]);
            }
        }
    }
    return best;
}

TEST(examples) {
    run({{1, 1, 0, 0, 0}, {1, 0, 0, 1, 1}, {0, 0, 1, 1, 0}, {0, 1, 0, 1, 0}}, 5);
    run({{1, 0, 1}, {0, 1, 0}}, 1);
    run({{0, 0}, {0, 0}}, 0);
}

TEST(edge_cases) {
    run({{1}}, 1);
    run({{0}}, 0);
    run({{1, 1, 0, 1, 1, 1}}, 3);
    run({{1}, {1}, {1}, {0}, {1}}, 3);
    run({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, 8);
    run({{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, 5);
    run({{1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}}, 1);
}

TEST(random) {
    Rng rng(82);
    for (int t = 0; t < 300; ++t) {
        int m = rng(1, 8), n = rng(1, 8);
        double p = rng.real();
        Grid grid(m, vector<int>(n));
        for (auto& row : grid) {
            for (int& x : row) {
                x = rng.coin(p) ? 1 : 0;
            }
        }
        run(grid, largest_island(grid));
    }
}

TEST(large) {
    const int n = 50;
    run(Grid(n, vector<int>(n, 1)), n * n);
    Grid grid(n, vector<int>(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            grid[r][c] = (r + c) % 2;
        }
    }
    run(grid, 1);
    for (int r = 0; r < n; ++r) {
        grid[r].assign(n, r % 2 == 0 ? 1 : 0);
    }
    for (int r = 1; r < n; r += 2) {
        grid[r][(r / 2) % 2 == 0 ? n - 1 : 0] = 1;
    }
    run(grid, 25 * 50 + 25);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            grid[r][c] = c < 24 ? 1 : c == 24 ? 0 : (r + c) % 2;
        }
    }
    run(grid, 50 * 24);
}

}
