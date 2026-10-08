#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Points = vector<vector<int>>;

static int brute(const Points& p) {
    int n = p.size(), best = min(n, 2);
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        x[i] = p[i][0], y[i] = p[i][1];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int ax = x[j] - x[i], ay = y[j] - y[i], on = 2;
            for (int k = j + 1; k < n; ++k) {
                on += ax * (y[k] - y[i]) == ay * (x[k] - x[i]);
            }
            best = max(best, on);
        }
    }
    return best;
}

static void run(const Points& points, int want) {
    Points arg = points;
    check(Solution().maxPoints(arg), want, "points", points);
}

static void run(const Points& points) { run(points, brute(points)); }

static Points hidden_line(Rng& rng, int k, int noise, int lim = 10000) {
    set<pair<int, int>> seen;
    Points out;
    auto add = [&](int x, int y) {
        if (abs(x) <= lim && abs(y) <= lim && seen.insert({x, y}).second) {
            out.push_back({x, y});
        }
    };
    int dx = rng(0, 12), dy = rng(-12, 12);
    if (dx == 0 && dy == 0) {
        dy = 1;
    }
    int x0 = rng(-lim, lim), y0 = rng(-lim, lim);
    for (int t = -k; t <= k && static_cast<int>(out.size()) < k; ++t) {
        add(x0 + t * dx, y0 + t * dy);
    }
    for (int t = 0; t < noise; ++t) {
        add(rng(-lim, lim), rng(-lim, lim));
    }
    rng.shuffle(out);
    return out;
}

TEST(examples) {
    run({{2, 1}, {4, 2}, {6, 3}, {3, 5}}, 3);
    run({{-3, 4}, {0, 4}, {5, 4}, {2, 1}, {2, 7}, {2, -6}, {2, 0}}, 4);
    run({{7, -3}}, 1);
}

TEST(edge_cases) {
    run({{0, 0}}, 1);
    run({{1, 2}, {3, 4}}, 2);
    run({{-10000, 10000}, {10000, -10000}}, 2);
    run({{-10000, -10000}, {10000, 10000}, {0, 0}}, 3);
    run({{-10000, 10000}, {10000, -10000}, {1, 1}, {0, 0}}, 3);
    run({{0, 0}, {1, 2}, {2, 1}, {3, 3}}, 2);
    run({{1, 5}, {-7, 5}, {3, 5}, {3, 6}, {0, 0}}, 3);
    run({{5, 0}, {5, 3}, {5, -3}, {5, 10}, {4, 0}, {6, 0}}, 4);
    run({{3, -3}, {0, 0}, {-2, 2}, {6, -6}, {1, 1}}, 4);
    run({{0, 0}, {2, 4}, {3, 6}, {-5, -10}, {1, 3}}, 4);
    run({{1, 1}, {3, 2}, {5, 3}, {7, 4}, {2, 3}, {4, 2}, {6, 1}}, 4);
    run({{0, 0}, {1, 1}, {2, 2}, {0, 1}, {1, 2}, {2, 3}, {3, 4}}, 4);
    run({{1, 1}, {2, 2}, {3, 3}, {4, 4}, {1, 2}, {2, 4}, {3, 6}}, 4);
}

TEST(nearly_parallel) {
    run({{-10000, -10000}, {10000, 9999}, {9999, 9998}}, 2);
    run({{-10000, 0}, {10000, 1}, {9999, 1}}, 2);
    run({{0, -10000}, {1, 10000}, {1, 9999}}, 2);
    run({{0, 0}, {9999, 9998}, {-9999, -9998}, {10000, 9999}, {-10000, -9999}}, 3);
    Points p = {{0, 0}};
    for (int k = 1; k <= 5; ++k) {
        for (int s : {-1, 1}) {
            p.push_back({s * k * 2000, s * k * 1999});
            p.push_back({s * k * 1999, s * k * 1998});
        }
    }
    run(p, 11);
    Points fan = {{0, 0}};
    for (int q = 1000; q <= 1032; ++q) {
        for (int k = 1; k * q <= 10000; ++k) {
            fan.push_back({k * q, k * (q - 1)});
        }
    }
    run(fan, 33);
}

TEST(random) {
    Rng rng(149);
    for (int k = 0; k < 400; ++k) {
        int lim = rng(1, 6), n = rng(1, 30);
        set<pair<int, int>> seen;
        Points p;
        for (int t = 0; t < n; ++t) {
            int x = rng(-lim, lim), y = rng(-lim, lim);
            if (seen.insert({x, y}).second) {
                p.push_back({x, y});
            }
        }
        run(p);
    }
    for (int k = 0; k < 200; ++k) {
        run(hidden_line(rng, rng(2, 20), rng(0, 30)));
    }
}

TEST(large) {
    Rng rng(1490);
    run(hidden_line(rng, 150, 150));
    run(hidden_line(rng, 7, 293));
    set<pair<int, int>> seen;
    Points grid;
    while (grid.size() < 300) {
        int x = rng(-15, 14) * 333, y = rng(-15, 14) * 333;
        if (seen.insert({x, y}).second) {
            grid.push_back({x, y});
        }
    }
    run(grid);
    Points line;
    for (int t = 0; t < 300; ++t) {
        line.push_back({-1000 + 7 * t, 9000 - 3 * t});
    }
    rng.shuffle(line);
    run(line, 300);
}

}
