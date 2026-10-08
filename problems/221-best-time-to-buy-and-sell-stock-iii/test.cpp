#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> prices, int want) {
    vector<int> arg = prices;
    check(Solution().maxProfit(arg), want, "prices", prices);
}

static int brute(const vector<int>& prices, size_t day = 0, bool holding = false, int buysLeft = 2) {
    if (day == prices.size()) return 0;
    int p = prices[day];
    int best = brute(prices, day + 1, holding, buysLeft);
    if (holding) {
        best = max(best, p + brute(prices, day + 1, false, buysLeft));
    } else if (buysLeft > 0) {
        best = max(best, -p + brute(prices, day + 1, true, buysLeft - 1));
    }
    return best;
}

static int best_split(const vector<int>& prices) {
    int n = prices.size();
    vector<int> left(n, 0), right(n, 0);
    for (int i = 1, low = prices[0]; i < n; ++i) {
        low = min(low, prices[i]);
        left[i] = max(left[i - 1], prices[i] - low);
    }
    for (int i = n - 2, high = prices[n - 1]; i >= 0; --i) {
        high = max(high, prices[i]);
        right[i] = max(right[i + 1], high - prices[i]);
    }
    int best = 0;
    for (int d = 0; d < n; ++d) {
        best = max(best, left[d] + right[d]);
    }
    return best;
}

TEST(examples) {
    run({2, 6, 1, 4, 3, 9}, 12);
    run({3, 5, 7, 8}, 5);
    run({9, 7, 4, 1}, 0);
}

TEST(edge_cases) {
    run({5}, 0);
    run({1, 2}, 1);
    run({2, 1}, 0);
    run({4, 4, 4}, 0);
    run({1, 5, 2, 6}, 8);
    run({1, 5, 2, 6, 3, 7}, 9);
    run({1, 9, 8, 9}, 9);
    run({3, 1, 9, 2, 10, 0, 4}, 16);
    run({0, 100000}, 100000);
    run({6, 1, 3, 2, 4, 7}, 7);
}

TEST(random) {
    Rng rng(123);
    for (int iter = 0; iter < 500; ++iter) {
        vector<int> prices = rng.ints(rng(1, 12), 0, rng.coin() ? 10 : 100000);
        run(prices, brute(prices));
    }
}

TEST(large) {
    const int n = 100000;
    vector<int> up(n);
    iota(up.begin(), up.end(), 0);
    run(up, n - 1);
    run(vector<int>(up.rbegin(), up.rend()), 0);
    vector<int> saw(n);
    for (int i = 0; i < n; ++i) {
        saw[i] = i % 2;
    }
    saw[30001] = 70000, saw[80001] = 100000;
    run(saw, 170000);
    Rng rng(1230);
    vector<int> prices = rng.ints(n, 0, 100000);
    run(prices, best_split(prices));
    for (int iter = 0; iter < 3; ++iter) {
        prices.assign(n, 0);
        prices[0] = rng(0, 100000);
        for (int i = 1; i < n; ++i) {
            prices[i] = clamp(prices[i - 1] + rng(-1000, 1000), 0, 100000);
        }
        run(prices, best_split(prices));
    }
}

}
