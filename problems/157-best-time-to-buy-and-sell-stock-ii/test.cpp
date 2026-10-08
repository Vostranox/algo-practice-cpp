#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> prices, int want) {
    vector<int> arg = prices;
    check(Solution().maxProfit(arg), want, "prices", prices);
}

static int brute(const vector<int>& p, size_t day, int bought) {
    if (day == p.size()) return 0;
    int best = brute(p, day + 1, bought);
    if (bought < 0) {
        best = max(best, brute(p, day + 1, p[day]));
    } else {
        best = max(best, p[day] - bought + brute(p, day + 1, -1));
    }
    return best;
}

static int64_t dp(const vector<int>& p) {
    int64_t hold = INT64_MIN / 2, cash = 0;
    for (int x : p) {
        int64_t h = max(hold, cash - x), c = max(cash, hold + x);
        hold = h, cash = c;
    }
    return cash;
}

TEST(examples) {
    run({3, 8, 2, 6, 6, 9}, 12);
    run({2, 4, 7, 11}, 9);
    run({9, 6, 6, 1}, 0);
}

TEST(edge_cases) {
    run({5}, 0);
    run({1, 2}, 1);
    run({2, 1}, 0);
    run({3, 3, 3}, 0);
    run({0, 10000}, 10000);
    run({1, 5, 3, 7}, 8);
    run({1, 2, 3, 2, 3, 4}, 4);
    run({1, 7, 2, 3, 6, 7, 6, 7}, 12);
    run({10000, 0, 10000, 0}, 10000);
}

TEST(random) {
    Rng rng(157);
    for (int i = 0; i < 400; ++i) {
        int n = rng(1, 11), hi = rng.coin() ? 5 : 10000;
        vector<int> prices = rng.ints(n, 0, hi);
        run(prices, brute(prices, 0, -1));
    }
}

TEST(large) {
    int n = 30000;
    vector<int> zigzag(n);
    for (int i = 0; i < n; ++i) {
        zigzag[i] = i % 2 ? 10000 : 0;
    }
    run(zigzag, 15000 * 10000);
    vector<int> up(n);
    for (int i = 0; i < n; ++i) {
        up[i] = i / 3;
    }
    run(up, 9999);
    reverse(up.begin(), up.end());
    run(up, 0);
    Rng rng(1570);
    for (int iter = 0; iter < 3; ++iter) {
        vector<int> prices = rng.ints(n, 0, 10000);
        run(prices, static_cast<int>(dp(prices)));
    }
}

}
