#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& heights, int want) {
    vector<int> arg = heights;
    check(Solution().largestRectangleArea(arg), want, "heights", heights);
}

static int brute(const vector<int>& h) {
    int64_t best = 0;
    for (size_t i = 0; i < h.size(); ++i) {
        int low = h[i];
        for (size_t j = i; j < h.size(); ++j) {
            low = min(low, h[j]);
            best = max(best, static_cast<int64_t>(low) * static_cast<int64_t>(j - i + 1));
        }
    }
    return static_cast<int>(best);
}

TEST(examples) {
    run({2, 4, 5, 3, 1, 3}, 9);
    run({6, 6}, 12);
    run({0, 7, 0}, 7);
}

TEST(edge_cases) {
    run({0}, 0);
    run({1}, 1);
    run({10000}, 10000);
    run({0, 0, 0}, 0);
    run({1, 2, 3, 4, 5}, 9);
    run({5, 4, 3, 2, 1}, 9);
    run({2, 1, 2}, 3);
    run({1, 1, 1, 1}, 4);
    run({5, 1, 5}, 5);
    run({3, 3, 1, 3, 3}, 6);
    run({4, 2, 0, 3, 2, 5}, 6);
    run({2, 2, 2, 6, 6, 2}, 12);
}

TEST(random) {
    Rng rng(27);
    for (int iter = 0; iter < 3000; ++iter) {
        int n = rng(1, 30);
        int top = rng.pick(vector<int>{1, 3, 10, 10000});
        vector<int> heights = rng.ints(n, 0, top);
        run(heights, brute(heights));
    }
}

TEST(large) {
    const int n = 100000;
    run(vector<int>(n, 10000), 10000 * n);
    vector<int> stairs(n);
    for (int i = 0; i < n; ++i) {
        stairs[i] = i / 10 + 1;
    }
    run(stairs, 10 * 5000 * 5001);
    reverse(stairs.begin(), stairs.end());
    run(stairs, 10 * 5000 * 5001);
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        h[i] = i % 2 ? 10000 : 0;
    }
    run(h, 10000);
    h.assign(n, 9999);
    h[n / 2] = 1;
    run(h, 9999 * (n / 2));
}

}
