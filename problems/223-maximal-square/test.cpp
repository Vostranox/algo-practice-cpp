#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<char>>;

static Grid G(initializer_list<string> rows) {
    Grid g;
    for (const string& r : rows) {
        g.emplace_back(r.begin(), r.end());
    }
    return g;
}

static void run(const Grid& matrix, int want) {
    Grid arg = matrix;
    check(Solution().maximalSquare(arg), want, "matrix", matrix);
}

static int brute(const Grid& g) {
    int m = g.size(), n = g[0].size(), best = 0;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            for (int s = 1; r + s <= m && c + s <= n; ++s) {
                bool ok = true;
                for (int i = r; i < r + s && ok; ++i) {
                    for (int j = c; j < c + s && ok; ++j) {
                        ok = g[i][j] == '1';
                    }
                }
                if (ok) {
                    best = max(best, s);
                }
            }
        }
    }
    return best * best;
}

static int by_prefix_sums(const Grid& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> P(m + 1, vector<int>(n + 1, 0));
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            P[r + 1][c + 1] = P[r][c + 1] + P[r + 1][c] - P[r][c] + (g[r][c] == '1');
        }
    }
    auto feasible = [&](int s) {
        for (int r = s; r <= m; ++r) {
            for (int c = s; c <= n; ++c) {
                if (P[r][c] - P[r - s][c] - P[r][c - s] + P[r - s][c - s] == s * s) return true;
            }
        }
        return false;
    };
    int lo = 0, hi = min(m, n);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (feasible(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo * lo;
}

static Grid random_grid(Rng& rng, int m, int n, double ones) {
    Grid g(m, vector<char>(n));
    for (auto& row : g) {
        for (char& x : row) {
            x = rng.coin(ones) ? '1' : '0';
        }
    }
    return g;
}

TEST(examples) {
    run(G({"1101", "1111", "0111", "1111"}), 9);
    run(G({"01", "10"}), 1);
    run(G({"0"}), 0);
}

TEST(edge_cases) {
    run(G({"1"}), 1);
    run(G({"00"}), 0);
    run(G({"11", "11"}), 4);
    run(G({"11111", "11111"}), 4);
    run(G({"111", "101", "111"}), 1);
    run(G({"11100", "11100", "11111", "00111", "00111"}), 9);
    run(G({"1111", "1111", "1110", "1111"}), 9);
    run(G({"0111", "0111", "0111"}), 9);
    run(G({"1", "1", "1"}), 1);
    run(G({"10111", "11111", "01111", "11110"}), 9);
}

TEST(random) {
    Rng rng(221);
    for (int iter = 0; iter < 400; ++iter) {
        Grid g = random_grid(rng, rng(1, 8), rng(1, 8), rng.pick(vector<double>{0.3, 0.7, 0.9}));
        run(g, brute(g));
    }
}

TEST(large) {
    run(Grid(300, vector<char>(300, '1')), 90000);
    run(Grid(300, vector<char>(300, '0')), 0);
    run(Grid(1, vector<char>(300, '1')), 1);
    run(Grid(300, vector<char>(1, '1')), 1);
    Grid g(300, vector<char>(300, '1'));
    g[299][299] = '0';
    run(g, 299 * 299);
    g[299][299] = '1', g[0][299] = '0';
    run(g, 299 * 299);
    g[0][299] = '1', g[150][150] = '0';
    run(g, 150 * 150);
    for (int i = 0; i < 300; ++i) {
        g[i][i] = '0';
    }
    run(g, 150 * 150);
    Rng rng(2210);
    for (double ones : {0.5, 0.9, 0.97, 0.995}) {
        g = random_grid(rng, 300, 300, ones);
        run(g, by_prefix_sums(g));
    }
    g = random_grid(rng, 300, 300, 0.6);
    for (int r = 101; r < 221; ++r) {
        for (int c = 37; c < 157; ++c) {
            g[r][c] = '1';
        }
    }
    run(g, by_prefix_sums(g));
}

}
