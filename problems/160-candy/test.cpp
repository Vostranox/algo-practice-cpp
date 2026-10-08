#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> ratings, int want) {
    vector<int> arg = ratings;
    check(Solution().candy(arg), want, "ratings", ratings);
}

static bool valid(const vector<int>& r, const vector<int>& c) {
    for (size_t i = 0; i < r.size(); ++i) {
        if (c[i] < 1) return false;
        if (i > 0 && r[i] > r[i - 1] && c[i] <= c[i - 1]) return false;
        if (i + 1 < r.size() && r[i] > r[i + 1] && c[i] <= c[i + 1]) return false;
    }
    return true;
}

static int exhaustive(const vector<int>& r) {
    int n = r.size(), best = INT_MAX;
    vector<int> c(n, 1);
    while (true) {
        if (valid(r, c)) {
            best = min(best, accumulate(c.begin(), c.end(), 0));
        }
        int i = 0;
        while (i < n && c[i] == n) {
            c[i++] = 1;
        }
        if (i == n) return best;
        ++c[i];
    }
}

static int64_t by_rating_order(const vector<int>& r) {
    int n = r.size();
    vector<int> order(n), c(n, 1);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return r[a] < r[b]; });
    for (int i : order) {
        if (i > 0 && r[i - 1] < r[i]) {
            c[i] = max(c[i], c[i - 1] + 1);
        }
        if (i + 1 < n && r[i + 1] < r[i]) {
            c[i] = max(c[i], c[i + 1] + 1);
        }
    }
    return accumulate(c.begin(), c.end(), int64_t{0});
}

TEST(examples) {
    run({2, 5, 3}, 4);
    run({4, 3, 2, 2, 6}, 9);
    run({1, 3, 5, 5, 5, 2}, 10);
}

TEST(edge_cases) {
    run({7}, 1);
    run({0, 0}, 2);
    run({1, 2}, 3);
    run({2, 1}, 3);
    run({1, 2, 2}, 4);
    run({1, 0, 2}, 5);
    run({1, 3, 2, 2, 1}, 7);
    run({5, 4, 3, 2, 1}, 15);
    run({3, 2, 1, 2, 3}, 11);
    run({1, 2, 3, 4, 3, 2, 1}, 16);
    run({1, 2, 5, 4, 3, 2, 1}, 18);
    run({1, 6, 10, 8, 7, 3, 2}, 18);
    run({1, 2, 3, 4, 1}, 11);
    run({2, 2, 2, 2}, 4);
    run({20000, 0, 20000}, 5);
}

TEST(random) {
    Rng rng(160);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> r = rng.ints(rng(1, 5), 0, 3);
        run(r, exhaustive(r));
    }
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> r = rng.ints(rng(1, 40), 0, rng.coin() ? 3 : 20000);
        run(r, static_cast<int>(by_rating_order(r)));
    }
}

TEST(large) {
    const int n = 20000;
    vector<int> up(n);
    iota(up.begin(), up.end(), 0);
    run(up, n * (n + 1) / 2);
    run(vector<int>(up.rbegin(), up.rend()), n * (n + 1) / 2);
    vector<int> down(n);
    for (int i = 0; i < n; ++i) {
        down[i] = 20000 - i;
    }
    run(down, n * (n + 1) / 2);
    vector<int> valley(n);
    for (int i = 0; i < n; ++i) {
        valley[i] = i < n / 2 ? n / 2 - i : i - n / 2 + 1;
    }
    run(valley, n / 2 * (n / 2 + 1));
    run(vector<int>(n, 7), n);
    vector<int> zigzag(n);
    for (int i = 0; i < n; ++i) {
        zigzag[i] = i % 2 ? 20000 : 0;
    }
    run(zigzag, n / 2 * 3);
    vector<int> peak(n);
    for (int i = 0; i < n; ++i) {
        peak[i] = i <= 5000 ? 15000 + i : 25000 - i;
    }
    run(peak, static_cast<int>(by_rating_order(peak)));
    Rng rng(1600);
    for (int hi : {2, 50, 20000}) {
        vector<int> r = rng.ints(n, 0, hi);
        run(r, static_cast<int>(by_rating_order(r)));
    }
    for (int k = 0; k < 20; ++k) {
        int top = rng(0, n - 1);
        vector<int> r(n);
        for (int i = 0; i < n; ++i) {
            r[i] = k % 2 ? abs(i - top) : 20000 - abs(i - top);
        }
        run(r, static_cast<int>(by_rating_order(r)));
    }
    vector<int> runs;
    while (static_cast<int>(runs.size()) < n) {
        vector<int> chunk = sorted(rng.ints(rng(1, 3000), 0, 20000));
        if (rng.coin()) {
            reverse(chunk.begin(), chunk.end());
        }
        runs.insert(runs.end(), chunk.begin(), chunk.end());
    }
    runs.resize(n);
    run(runs, static_cast<int>(by_rating_order(runs)));
}

}
