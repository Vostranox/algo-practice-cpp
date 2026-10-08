#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Intervals = vector<vector<int>>;

static void run(Intervals intervals, vector<int> newInterval, Intervals want) {
    Intervals a = intervals;
    vector<int> b = newInterval;
    check(Solution().insert(a, b), want, "intervals", intervals, "newInterval", newInterval);
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

static Intervals with(Intervals v, const vector<int>& extra) {
    v.push_back(extra);
    return v;
}

static Intervals sorted_disjoint(Rng& rng, int hi, int gap, double keep, int limit = 10000) {
    Intervals out;
    int x = rng(0, gap);
    while (static_cast<int>(out.size()) < limit && rng.coin(keep)) {
        int e = x + rng(0, 3);
        if (e > hi) break;
        out.push_back({x, e});
        x = e + 1 + rng(0, gap);
    }
    return out;
}

static Intervals concat(const Intervals& a, const Intervals& b, const Intervals& c) {
    Intervals out = a;
    out.insert(out.end(), b.begin(), b.end());
    out.insert(out.end(), c.begin(), c.end());
    return out;
}

static Intervals slice(const Intervals& v, size_t from, size_t to) {
    return Intervals(v.begin() + from, v.begin() + min(to, v.size()));
}

TEST(examples) {
    run({{1, 2}, {5, 8}, {10, 12}}, {6, 11}, {{1, 2}, {5, 12}});
    run({{1, 3}, {6, 7}}, {4, 5}, {{1, 3}, {4, 5}, {6, 7}});
    run({{1, 3}, {7, 9}}, {3, 7}, {{1, 9}});
}

TEST(edge_cases) {
    run({}, {2, 4}, {{2, 4}});
    run({{5, 7}}, {1, 2}, {{1, 2}, {5, 7}});
    run({{1, 2}}, {5, 7}, {{1, 2}, {5, 7}});
    run({{1, 2}}, {2, 3}, {{1, 3}});
    run({{3, 4}}, {1, 3}, {{1, 4}});
    run({{1, 9}}, {3, 4}, {{1, 9}});
    run({{3, 4}}, {1, 9}, {{1, 9}});
    run({{1, 2}, {4, 5}, {7, 8}}, {0, 10}, {{0, 10}});
    run({{1, 1}, {3, 3}}, {2, 2}, {{1, 1}, {2, 2}, {3, 3}});
    run({{1, 1}, {3, 3}}, {1, 3}, {{1, 3}});
    run({{0, 0}}, {0, 0}, {{0, 0}});
    run({{0, 2}, {5, 6}, {9, 100000}}, {3, 4}, {{0, 2}, {3, 4}, {5, 6}, {9, 100000}});
    run({{0, 2}, {5, 6}, {9, 100000}}, {6, 9}, {{0, 2}, {5, 100000}});
}

TEST(random) {
    Rng rng(57);
    vector<int> spans = {0, 2, 6, 20};
    for (int it = 0; it < 500; ++it) {
        Intervals intervals = sorted_disjoint(rng, 20, rng.coin() ? 1 : 3, 0.9);
        int a = rng(0, 20);
        int b = rng(a, min(20, a + rng.pick(spans)));
        run(intervals, {a, b}, covered_runs(with(intervals, {a, b})));
    }
}

TEST(large) {
    Intervals base;
    for (int i = 0; i < 10000; ++i) {
        base.push_back({10 * i, 10 * i + 5});
    }
    size_t n = base.size();
    run(base, {23, 47}, concat(slice(base, 0, 2), {{20, 47}}, slice(base, 5, n)));
    run(base, {6, 9}, concat(slice(base, 0, 1), {{6, 9}}, slice(base, 1, n)));
    run(base, {5, 10}, concat({}, {{0, 15}}, slice(base, 2, n)));
    run(base, {0, 0}, base);
    run(base, {0, 100000}, {{0, 100000}});
    run(base, {99996, 100000}, concat(base, {{99996, 100000}}, {}));
    run(base, {50000, 60003}, concat(slice(base, 0, 5000), {{50000, 60005}}, slice(base, 6001, n)));
    run(base, {12345, 12347}, concat(slice(base, 0, 1234), {{12340, 12347}}, slice(base, 1235, n)));
    run(base, {99995, 99995}, base);
    Rng rng(8);
    vector<int> spans = {5, 500, 50000};
    for (int it = 0; it < 3; ++it) {
        Intervals intervals = sorted_disjoint(rng, 100000, 16, 1.0);
        int a = rng(0, 100000);
        int b = rng(a, min(100000, a + rng.pick(spans)));
        run(intervals, {a, b}, covered_runs(with(intervals, {a, b})));
    }
}

}
