#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> prices, int want) {
    vector<int> arg = prices;
    check(Solution().maxProfit(arg), want, "prices", prices);
}

static int brute(const vector<int>& p) {
    int best = 0, n = p.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            best = max(best, p[j] - p[i]);
        }
    }
    return best;
}

TEST(examples) {
    run({8, 3, 6, 1, 5, 4}, 4);
    run({9, 7, 4, 2}, 0);
    run({4, 9, 1, 3}, 5);
}

TEST(edge_cases) {
    run({5}, 0);
    run({1, 2}, 1);
    run({2, 1}, 0);
    run({3, 3, 3}, 0);
    run({0, 10000}, 10000);
    run({2, 4, 1}, 2);
    run({3, 8, 1, 2, 9, 0}, 8);
    run({10000, 0}, 0);
}

TEST(random) {
    Rng rng(15);
    for (int i = 0; i < 300; ++i) {
        vector<int> prices = rng.ints(rng(1, 12), 0, 20);
        run(prices, brute(prices));
    }
}

TEST(large) {
    Rng rng(1515);
    const int n = 100000;
    vector<int> falling(n);
    for (int i = 0; i < n; ++i) {
        falling[i] = 10000 - i / 10;
    }
    run(falling, 0);
    const int k = 60000;
    vector<int> spiked = falling;
    spiked[k] = 10000;
    run(spiked, 10000 - falling[k - 1]);
    vector<int> prices = rng.ints(n, 3000, 7000);
    prices[30000] = 0;
    prices[70000] = 10000;
    run(prices, 10000);
    vector<int> rising(n);
    for (int i = 0; i < n; ++i) {
        rising[i] = i / 10;
    }
    run(rising, (n - 1) / 10);
}

}
