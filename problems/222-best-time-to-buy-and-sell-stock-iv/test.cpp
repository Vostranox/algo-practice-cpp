#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int k, vector<int> prices, int want) {
    vector<int> arg = prices;
    check(Solution().maxProfit(k, arg), want, "k", k, "prices", prices);
}

static int brute(const vector<int>& prices, int buysLeft, size_t day = 0, bool holding = false) {
    if (day == prices.size()) return 0;
    int p = prices[day];
    int best = brute(prices, buysLeft, day + 1, holding);
    if (holding) {
        best = max(best, p + brute(prices, buysLeft, day + 1, false));
    } else if (buysLeft > 0) {
        best = max(best, -p + brute(prices, buysLeft - 1, day + 1, true));
    }
    return best;
}

static int by_last_sale(int k, const vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> profit(k + 1, vector<int>(n, 0));
    for (int j = 1; j <= k; ++j) {
        int bestBuy = -prices[0];
        for (int i = 1; i < n; ++i) {
            profit[j][i] = max(profit[j][i - 1], prices[i] + bestBuy);
            bestBuy = max(bestBuy, profit[j - 1][i] - prices[i]);
        }
    }
    return profit[k][n - 1];
}

TEST(examples) {
    run(2, {3, 1, 4, 1, 5, 9, 2, 6}, 12);
    run(3, {3, 1, 4, 1, 5, 9, 2, 6}, 15);
    run(100, {1, 3, 2, 8}, 8);
}

TEST(edge_cases) {
    run(1, {5}, 0);
    run(100, {5}, 0);
    run(1, {1, 2}, 1);
    run(1, {2, 1}, 0);
    run(1, {3, 1, 4, 1, 5, 9, 2, 6}, 8);
    run(4, {3, 1, 4, 1, 5, 9, 2, 6}, 15);
    run(1, {1, 5, 2, 6}, 5);
    run(2, {1, 5, 2, 6}, 8);
    run(2, {1, 9, 8, 9, 0, 3}, 11);
    run(100, {7, 6, 5, 4}, 0);
    run(100, {0, 1000, 0, 1000}, 2000);
    run(1, {0, 1000, 0, 1000}, 1000);
}

TEST(random) {
    Rng rng(188);
    for (int iter = 0; iter < 600; ++iter) {
        vector<int> prices = rng.ints(rng(1, 10), 0, rng.coin() ? 10 : 1000);
        int k = rng.coin(0.8) ? rng(1, 5) : rng(6, 100);
        run(k, prices, brute(prices, k));
    }
}

TEST(large) {
    const int n = 1000;
    vector<int> saw(n);
    for (int i = 0; i < n; ++i) {
        saw[i] = i % 2 ? 1000 : 0;
    }
    run(100, saw, 100000);
    run(100, vector<int>(saw.begin(), saw.begin() + 200), 100000);
    run(1, saw, 1000);
    vector<int> up(n);
    iota(up.begin(), up.end(), 0);
    run(50, up, 999);
    run(100, vector<int>(up.rbegin(), up.rend()), 0);
    Rng rng(1880);
    vector<int> peaks = rng.ints(n / 2, 1, 1000), prices;
    for (int p : peaks) {
        prices.insert(prices.end(), {0, p});
    }
    for (int k : {1, 7, 100}) {
        vector<int> top = sorted(peaks);
        run(k, prices, accumulate(top.end() - k, top.end(), 0));
    }
}

TEST(large_random) {
    const int n = 1000;
    Rng rng(1881);
    for (int k : {2, 13, 64, 100}) {
        vector<int> prices = rng.ints(n, 0, 1000);
        run(k, prices, by_last_sale(k, prices));
        vector<int> walk(n);
        walk[0] = rng(0, 1000);
        for (int i = 1; i < n; ++i) {
            walk[i] = clamp(walk[i - 1] + rng(-30, 30), 0, 1000);
        }
        run(k, walk, by_last_sale(k, walk));
    }
}

}
