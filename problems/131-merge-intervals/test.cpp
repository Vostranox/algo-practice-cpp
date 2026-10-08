#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Intervals = vector<vector<int>>;

static void run(Intervals intervals, Intervals want) {
    Intervals arg = intervals;
    check(Solution().merge(arg), want, "intervals", intervals);
}

static Intervals covered_runs(const Intervals& intervals) {
    int hi = 0;
    for (auto& iv : intervals) {
        hi = max(hi, iv[1]);
    }
    vector<char> covered(2 * hi + 2, 0);
    for (auto& iv : intervals) {
        for (int p = 2 * iv[0]; p <= 2 * iv[1]; ++p) {
            covered[p] = 1;
        }
    }
    Intervals out;
    for (int p = 0; p < static_cast<int>(covered.size()); ++p) {
        if (!covered[p]) continue;
        int q = p;
        while (covered[q + 1]) {
            ++q;
        }
        out.push_back({p / 2, q / 2});
        p = q;
    }
    return out;
}

TEST(examples) {
    run({{8, 10}, {1, 4}, {2, 6}, {12, 15}}, {{1, 6}, {8, 10}, {12, 15}});
    run({{3, 5}, {5, 9}}, {{3, 9}});
    run({{2, 3}, {1, 10}, {4, 4}}, {{1, 10}});
}

TEST(edge_cases) {
    run({{1, 1}}, {{1, 1}});
    run({{1, 2}, {3, 4}}, {{1, 2}, {3, 4}});
    run({{3, 4}, {1, 2}}, {{1, 2}, {3, 4}});
    run({{1, 4}, {2, 3}}, {{1, 4}});
    run({{1, 4}, {0, 0}}, {{0, 0}, {1, 4}});
    run({{1, 4}, {0, 1}}, {{0, 4}});
    run({{2, 5}, {2, 5}}, {{2, 5}});
    run({{0, 0}, {0, 0}}, {{0, 0}});
    run({{3, 4}, {1, 2}, {2, 3}}, {{1, 4}});
    run({{5, 5}, {1, 3}, {4, 4}}, {{1, 3}, {4, 4}, {5, 5}});
    run({{1, 3}, {6, 9}, {2, 7}}, {{1, 9}});
    run({{0, 10000}, {5000, 5000}}, {{0, 10000}});
    run({{1, 10}, {2, 3}, {11, 12}}, {{1, 10}, {11, 12}});
}

TEST(random) {
    Rng rng(56);
    vector<int> spans = {0, 0, 1, 2, 3, 6};
    for (int it = 0; it < 500; ++it) {
        Intervals intervals(rng(1, 10));
        for (auto& iv : intervals) {
            int s = rng(0, 20);
            iv = {s, min(20, s + rng.pick(spans))};
        }
        run(intervals, covered_runs(intervals));
    }
}

TEST(large) {
    const int n = 10000;
    Rng rng(9);
    Intervals points, chain, nested, pairs, want_points, want_pairs;
    for (int i = 0; i < n; ++i) {
        points.push_back({i, i});
        chain.push_back({i, i + 1});
        nested.push_back({i % 5001, n - i % 5001});
    }
    want_points = points;
    for (int rep = 0; rep < 3; ++rep) {
        for (int k = 0; k < 3333; ++k) {
            pairs.push_back({3 * k, 3 * k + 1});
        }
    }
    for (int k = 0; k < 3333; ++k) {
        want_pairs.push_back({3 * k, 3 * k + 1});
    }
    for (auto* v : {&points, &chain, &nested, &pairs}) {
        rng.shuffle(*v);
    }
    run(points, want_points);
    run(chain, {{0, n}});
    run(nested, {{0, n}});
    run(pairs, want_pairs);
    vector<int> spans = {0, 0, 0, 1, 2};
    for (int it = 0; it < 4; ++it) {
        Intervals intervals(n);
        for (auto& iv : intervals) {
            int s = rng(0, n);
            iv = {s, min(n, s + rng.pick(spans))};
        }
        run(intervals, covered_runs(intervals));
    }
}

}
