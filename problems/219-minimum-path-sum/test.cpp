#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;

static void run(const Grid& grid, int want) {
    Grid arg = grid;
    check(Solution().minPathSum(arg), want, "grid", grid);
}

static int every_route(const Grid& g, int r = 0, int c = 0) {
    int m = g.size(), n = g[0].size();
    if (r == m - 1 && c == n - 1) return g[r][c];
    int best = INT_MAX;
    if (r + 1 < m) {
        best = min(best, every_route(g, r + 1, c));
    }
    if (c + 1 < n) {
        best = min(best, every_route(g, r, c + 1));
    }
    return g[r][c] + best;
}

static int dijkstra(const Grid& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> heap;
    heap.push({dist[0][0] = g[0][0], 0, 0});
    while (!heap.empty()) {
        auto [d, r, c] = heap.top();
        heap.pop();
        if (d > dist[r][c]) continue;
        for (auto [nr, nc] : {pair{r + 1, c}, pair{r, c + 1}}) {
            if (nr < m && nc < n && d + g[nr][nc] < dist[nr][nc]) {
                heap.push({dist[nr][nc] = d + g[nr][nc], nr, nc});
            }
        }
    }
    return dist[m - 1][n - 1];
}

static Grid random_grid(Rng& rng, int m, int n, int hi) {
    Grid g(m);
    for (auto& row : g) {
        row = rng.ints(n, 0, hi);
    }
    return g;
}

TEST(examples) {
    run({{1, 4, 2}, {3, 1, 6}, {5, 2, 1}}, 8);
    run({{7, 0, 9}}, 16);
    run({{2, 9}, {1, 3}, {8, 0}}, 6);
}

TEST(edge_cases) {
    run({{0}}, 0);
    run({{200}}, 200);
    run({{5}, {3}, {1}}, 9);
    run({{1, 2}, {3, 4}}, 7);
    run({{1, 100, 1, 1}, {1, 1, 1, 100}, {100, 100, 1, 1}}, 6);
    run({{1, 2, 9}, {5, 9, 9}, {1, 1, 1}}, 9);
    run({{0, 0, 0}, {0, 0, 0}}, 0);
}

TEST(random) {
    Rng rng(219);
    for (int iter = 0; iter < 300; ++iter) {
        Grid g = random_grid(rng, rng(1, 7), rng(1, 7), rng.coin() ? 3 : 200);
        run(g, every_route(g));
    }
}

TEST(large) {
    Rng rng(640);
    run(Grid(200, vector<int>(200, 0)), 0);
    run(Grid(200, vector<int>(200, 200)), 399 * 200);
    Grid g(200, vector<int>(200, 200));
    for (int r = 0, c = 0;;) {
        g[r][c] = 1;
        if (r == 199 && c == 199) break;
        if (c == 199 || (r < 199 && rng.coin())) {
            ++r;
        } else {
            ++c;
        }
    }
    run(g, 399);
    for (int hi : {200, 1, 10}) {
        g = random_grid(rng, 200, 200, hi);
        run(g, dijkstra(g));
    }
    g = random_grid(rng, 1, 200, 200);
    run(g, dijkstra(g));
    g = random_grid(rng, 200, 1, 200);
    run(g, dijkstra(g));
}

}
