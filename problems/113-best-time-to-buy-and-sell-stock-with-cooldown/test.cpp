#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> prices, int want) {
    vector<int> arg = prices;
    check(Solution().maxProfit(arg), want, "prices", prices);
}

static int brute(const vector<int>& prices, size_t day = 0, bool holding = false, bool cooldown = false) {
    if (day == prices.size()) return 0;
    int p = prices[day];
    int best = brute(prices, day + 1, holding, false);
    if (holding) {
        best = max(best, p + brute(prices, day + 1, false, true));
    } else if (!cooldown) {
        best = max(best, -p + brute(prices, day + 1, true, false));
    }
    return best;
}

static int by_last_sale(const vector<int>& prices) {
    int n = prices.size();
    vector<int> done(n, 0);
    int bestBuy = -prices[0];
    for (int i = 1; i < n; ++i) {
        done[i] = max(done[i - 1], prices[i] + bestBuy);
        bestBuy = max(bestBuy, (i >= 2 ? done[i - 2] : 0) - prices[i]);
    }
    return done[n - 1];
}

TEST(examples) {
    run({3, 8, 1, 6}, 5);
    run({1, 4, 2, 7}, 6);
    run({7, 5, 3}, 0);
}

TEST(edge_cases) {
    run({1}, 0);
    run({1, 2}, 1);
    run({2, 1}, 0);
    run({5, 5, 5, 5}, 0);
    run({1, 2, 3, 0, 2}, 3);
    run({1, 2, 4}, 3);
    run({1, 5, 1, 1, 5}, 8);
    run({0, 1000}, 1000);
}

TEST(random) {
    Rng rng(1130);
    for (int iter = 0; iter < 400; ++iter) {
        vector<int> prices = rng.ints(rng(1, 12), 0, 10);
        run(prices, brute(prices));
    }
}

TEST(large) {
    vector<int> saw;
    for (int i = 0; i < 2500; ++i) {
        saw.insert(saw.end(), {0, 1000});
    }
    run(saw, 1000 * 1250);
    Rng rng(1131);
    vector<int> rising = sorted(rng.ints(5000, 0, 1000));
    run(rising, rising.back() - rising.front());
    run(vector<int>(rising.rbegin(), rising.rend()), 0);
    for (int iter = 0; iter < 3; ++iter) {
        vector<int> prices = rng.ints(5000, 0, 1000);
        run(prices, by_last_sale(prices));
    }
}

}
