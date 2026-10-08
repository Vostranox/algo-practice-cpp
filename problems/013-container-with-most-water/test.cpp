#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> height, int want) {
    vector<int> arg = height;
    check(Solution().maxArea(arg), want, "height", height);
}

static int brute(const vector<int>& h) {
    int best = 0, n = h.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            best = max(best, min(h[i], h[j]) * (j - i));
        }
    }
    return best;
}

static int oracle(const vector<int>& h) {
    int n = h.size();
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return h[a] > h[b]; });
    int lo = n, hi = -1;
    int64_t best = 0;
    for (int k = 0; k < n;) {
        int e = k;
        while (e < n && h[order[e]] == h[order[k]]) {
            ++e;
        }
        for (int q = k; q < e; ++q) {
            lo = min(lo, order[q]), hi = max(hi, order[q]);
        }
        for (int q = k; q < e; ++q) {
            best = max(best, static_cast<int64_t>(h[order[q]]) * max(order[q] - lo, hi - order[q]));
        }
        k = e;
    }
    return static_cast<int>(best);
}

TEST(examples) {
    run({2, 5, 4, 1, 6, 3}, 15);
    run({6, 1, 1, 1, 1, 1, 2}, 12);
    run({7, 7}, 7);
}

TEST(edge_cases) {
    run({0, 0}, 0);
    run({1, 1}, 1);
    run({10000, 10000}, 10000);
    run({0, 10000, 0}, 0);
    run({1, 10000, 10000, 1}, 10000);
    run({5, 4, 3, 2, 1}, 6);
    run({1, 2, 3, 4, 5}, 6);
    run({4, 0, 0, 1}, 3);
    run({3, 9, 3, 4, 7, 2, 12, 6}, 45);
}

TEST(random) {
    Rng rng(13);
    for (int i = 0; i < 300; ++i) {
        vector<int> height = rng.ints(rng(2, 12), 0, 12);
        run(height, brute(height));
    }
}

TEST(large) {
    Rng rng(1313);
    const int n = 100000;
    run(vector<int>(n, 10000), 10000 * (n - 1));
    vector<int> rising(n);
    for (int i = 0; i < n; ++i) {
        rising[i] = i / 10;
    }
    run(rising, oracle(rising));
    for (int c = 0; c < 2; ++c) {
        vector<int> height = rng.ints(n, 0, 10000);
        run(height, oracle(height));
    }
    vector<int> low = rng.ints(n, 0, 50);
    low[20000] = 9000;
    low[70000] = 9500;
    run(low, oracle(low));
}

}
