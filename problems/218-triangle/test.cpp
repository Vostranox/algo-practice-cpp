#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Rows = vector<vector<int>>;

static void run(const Rows& triangle, int want) {
    Rows arg = triangle;
    check(Solution().minimumTotal(arg), want, "triangle", triangle);
}

static int every_path(const Rows& t) {
    int n = t.size(), best = INT_MAX;
    for (int mask = 0; mask < 1 << (n - 1); ++mask) {
        int j = 0, sum = t[0][0];
        for (int i = 1; i < n; ++i) {
            sum += t[i][j += mask >> (i - 1) & 1];
        }
        best = min(best, sum);
    }
    return best;
}

static int top_down(const Rows& t) {
    vector<int64_t> reach = {t[0][0]};
    for (size_t i = 1; i < t.size(); ++i) {
        vector<int64_t> next(i + 1, INT64_MAX);
        for (size_t j = 0; j <= i; ++j) {
            if (j < i) {
                next[j] = min(next[j], reach[j]);
            }
            if (j > 0) {
                next[j] = min(next[j], reach[j - 1]);
            }
            next[j] += t[i][j];
        }
        reach = next;
    }
    return static_cast<int>(*min_element(reach.begin(), reach.end()));
}

static Rows random_triangle(Rng& rng, int n, int lo, int hi) {
    Rows t;
    for (int i = 0; i < n; ++i) {
        t.push_back(rng.ints(i + 1, lo, hi));
    }
    return t;
}

TEST(examples) {
    run({{3}, {7, 4}, {2, 9, 1}, {6, 5, 8, 4}}, 12);
    run({{1}, {2, 3}, {9, 8, 1}}, 5);
    run({{-5}}, -5);
}

TEST(edge_cases) {
    run({{0}}, 0);
    run({{10000}}, 10000);
    run({{-1}, {2, 3}}, 1);
    run({{-1}, {-2, -3}}, -4);
    run({{1}, {1, 1}, {1, 1, 1}}, 3);
    run({{1}, {2, 3}, {4, 5, 6}, {7, 8, 9, -100}}, -90);
    run({{0}, {5, -1}, {-20, 7, 7}}, -15);
    run({{1}, {2, 3}, {10, 10, 1}}, 5);
}

TEST(random) {
    Rng rng(218);
    for (int iter = 0; iter < 300; ++iter) {
        Rows t = random_triangle(rng, rng(1, 12), -10, 10);
        run(t, every_path(t));
    }
}

TEST(large) {
    const int n = 200;
    Rng rng(1200);
    Rows t;
    for (int i = 0; i < n; ++i) {
        t.push_back(vector<int>(i + 1, 10000));
    }
    run(t, 2000000);
    for (auto& row : t) {
        for (int& x : row) {
            x = -10000;
        }
    }
    run(t, -2000000);
    for (auto& row : t) {
        for (int& x : row) {
            x = 10000;
        }
    }
    for (int i = 0, j = 0; i < n; j += rng(0, 1), ++i) {
        t[i][j] = -10000;
    }
    run(t, -2000000);
    for (auto [lo, hi] : vector<pair<int, int>>{{-10000, 10000}, {0, 10000}, {-10000, 0}, {-3, 3}}) {
        t = random_triangle(rng, n, lo, hi);
        run(t, top_down(t));
    }
}

}
