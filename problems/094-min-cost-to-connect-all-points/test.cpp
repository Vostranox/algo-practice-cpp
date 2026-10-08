#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Points = vector<vector<int>>;

static void run(const Points& points, int64_t want) {
    Points arg = points;
    check(static_cast<int64_t>(Solution().minCostConnectPoints(arg)), want, "points", points);
}

static int64_t mst(const Points& p) {
    int n = p.size();
    vector<tuple<int64_t, int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.emplace_back(llabs(static_cast<int64_t>(p[i][0]) - p[j][0]) + llabs(static_cast<int64_t>(p[i][1]) - p[j][1]), i, j);
        }
    }
    sort(edges.begin(), edges.end());
    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);
    auto find = [&](int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    };
    int64_t total = 0;
    for (auto [w, i, j] : edges) {
        int a = find(i), b = find(j);
        if (a != b) {
            parent[a] = b, total += w;
        }
    }
    return total;
}

TEST(examples) {
    run({{0, 0}, {3, 0}, {3, 4}, {10, 4}}, 14);
    run({{1, 1}, {-1, -1}, {1, -1}}, 4);
    run({{5, -7}}, 0);
}

TEST(edge_cases) {
    run({{-1000000, -1000000}, {1000000, 1000000}}, 4000000);
    run({{0, 0}, {0, 5}, {0, 2}, {0, 9}}, 9);
    run({{0, 0}, {0, 1}, {1, 0}, {1, 1}}, 3);
    run({{2, 2}, {-3, 7}, {0, 0}, {8, -1}, {4, 4}}, mst({{2, 2}, {-3, 7}, {0, 0}, {8, -1}, {4, 4}}));
    run({{0, 0}, {10, 0}, {5, 1}}, 12);
}

TEST(random) {
    Rng rng(94);
    for (int t = 0; t < 300; ++t) {
        int n = rng(1, 30), r = rng.pick(vector<int>{5, 50, 1000000});
        set<pair<int, int>> pts;
        while (static_cast<int>(pts.size()) < n && static_cast<int64_t>(pts.size()) < (int64_t{2} * r + 1) * (int64_t{2} * r + 1)) {
            pts.insert({rng(-r, r), rng(-r, r)});
        }
        Points points;
        for (auto [x, y] : pts) {
            points.push_back({x, y});
        }
        rng.shuffle(points);
        run(points, mst(points));
    }
}

TEST(large) {
    Rng rng(940);
    Points points;
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 25; ++j) {
            points.push_back({7 * i - 100, 7 * j + 3});
        }
    }
    rng.shuffle(points);
    run(points, 999 * 7);
    vector<int> xs, ys;
    set<int> used;
    while (used.size() < 1000) {
        used.insert(rng(-1000000, 1000000));
    }
    xs.assign(used.begin(), used.end());
    for (int i = 0; i < 1000; ++i) {
        ys.push_back(rng(-1000000, 1000000));
    }
    sort(ys.begin(), ys.end());
    points.clear();
    for (int i = 0; i < 1000; ++i) {
        points.push_back({xs[i], ys[i]});
    }
    rng.shuffle(points);
    run(points, static_cast<int64_t>(xs.back() - xs.front()) + (ys.back() - ys.front()));
    set<pair<int, int>> pts;
    while (pts.size() < 300) {
        pts.insert({rng(-1000000, 1000000), rng(-1000000, 1000000)});
    }
    points.clear();
    for (auto [x, y] : pts) {
        points.push_back({x, y});
    }
    rng.shuffle(points);
    run(points, mst(points));
}

}
