#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;

static void run(const Grid& grid, int want) {
    Grid arg = grid;
    check(Solution().swimInWater(arg), want, "grid", grid);
}

static bool reachable(const Grid& g, int t) {
    int n = g.size();
    if (g[0][0] > t) return false;
    vector<vector<bool>> seen(n, vector<bool>(n));
    vector<pair<int, int>> stack{{0, 0}};
    seen[0][0] = true;
    while (!stack.empty()) {
        auto [r, c] = stack.back();
        stack.pop_back();
        if (r == n - 1 && c == n - 1) return true;
        int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        for (int d = 0; d < 4; ++d) {
            int x = r + dr[d], y = c + dc[d];
            if (x >= 0 && x < n && y >= 0 && y < n && !seen[x][y] && g[x][y] <= t) {
                seen[x][y] = true;
                stack.push_back({x, y});
            }
        }
    }
    return false;
}

static int swim(const Grid& g) {
    int lo = 0, hi = g.size() * g.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (reachable(g, mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

static Grid random_grid(Rng& rng, int n) {
    vector<int> vals(n * n);
    iota(vals.begin(), vals.end(), 0);
    rng.shuffle(vals);
    Grid g(n, vector<int>(n));
    for (int i = 0; i < n * n; ++i) {
        g[i / n][i % n] = vals[i];
    }
    return g;
}

TEST(examples) {
    run({{0, 3}, {1, 2}}, 2);
    run({{0, 1, 2}, {7, 8, 3}, {6, 5, 4}}, 4);
    run({{0, 5, 1}, {2, 8, 3}, {7, 6, 4}}, 5);
}

TEST(edge_cases) {
    run({{0}}, 0);
    run({{3, 0}, {1, 2}}, 3);
    run({{0, 1}, {2, 3}}, 3);
    run({{0, 2}, {1, 3}}, 3);
    run({{0, 1, 2, 3, 4}, {24, 23, 22, 21, 5}, {12, 13, 14, 15, 16}, {11, 17, 18, 19, 20}, {10, 9, 8, 7, 6}}, 16);
}

TEST(random) {
    Rng rng(96);
    for (int t = 0; t < 300; ++t) {
        Grid g = random_grid(rng, rng(1, 8));
        run(g, swim(g));
    }
    for (int t = 0; t < 5; ++t) {
        Grid g = random_grid(rng, 50);
        run(g, swim(g));
    }
}

TEST(large) {
    Rng rng(960);
    const int n = 50;
    for (int t = 0; t < 3; ++t) {
        vector<int> high(2 * n), low(n * n - 2 * n);
        iota(high.begin(), high.end(), n * n - 2 * n);
        iota(low.begin(), low.end(), 0);
        rng.shuffle(high);
        rng.shuffle(low);
        Grid g(n, vector<int>(n));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                auto& from = (r == 15 || r == 35) ? high : low;
                g[r][c] = from.back();
                from.pop_back();
            }
        }
        run(g, max(*min_element(g[15].begin(), g[15].end()), *min_element(g[35].begin(), g[35].end())));
    }
    Grid g(n, vector<int>(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            g[r][c] = r * n + (r % 2 == 0 ? c : n - 1 - c);
        }
    }
    run(g, 49 * 50);
}

}
