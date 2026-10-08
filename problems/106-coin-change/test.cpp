#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> coins, int amount, int want) {
    vector<int> arg = coins;
    check(Solution().coinChange(arg, amount), want, "coins", coins, "amount", amount);
}

static int brute(const vector<int>& coins, int amount, size_t i = 0) {
    if (i == coins.size()) return amount == 0 ? 0 : -1;
    int best = -1;
    for (int k = 0; static_cast<int64_t>(k) * coins[i] <= amount; ++k) {
        int rest = brute(coins, amount - k * coins[i], i + 1);
        if (rest >= 0 && (best < 0 || k + rest < best)) {
            best = k + rest;
        }
    }
    return best;
}

static int bfs(const vector<int>& coins, int amount) {
    vector<int> dist(amount + 1, -1);
    dist[0] = 0;
    deque<int> q{0};
    while (!q.empty()) {
        int a = q.front();
        q.pop_front();
        for (int c : coins) {
            if (c <= amount - a && dist[a + c] < 0) {
                dist[a + c] = dist[a] + 1;
                q.push_back(a + c);
            }
        }
    }
    return dist[amount];
}

TEST(examples) {
    run({1, 4, 6}, 8, 2);
    run({5, 10}, 3, -1);
    run({7}, 0, 0);
}

TEST(edge_cases) {
    run({1}, 1, 1);
    run({1}, 0, 0);
    run({2}, 3, -1);
    run({3, 7}, 11, -1);
    run({3, 7}, 12, 4);
    run({3, 7}, 14, 2);
    run({9, 6, 5, 1}, 11, 2);
    run({INT_MAX}, 2, -1);
    run({1, INT_MAX}, 2, 2);
    run({5, 2, 1}, 11, 3);
    run({186, 419, 83, 408}, 6249, 20);
}

TEST(random) {
    Rng rng(1060);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> pool(15);
        iota(pool.begin(), pool.end(), 1);
        rng.shuffle(pool);
        vector<int> coins(pool.begin(), pool.begin() + rng(1, 3));
        int amount = rng(0, 40);
        run(coins, amount, brute(coins, amount));
    }
}

TEST(large) {
    run({1, 2, 5}, 10000, 2000);
    vector<int> evens;
    for (int k = 1; k <= 12; ++k) {
        evens.push_back(2 * k);
    }
    run(evens, 9999, -1);
    run({9973, 10000, 1}, 10000, 1);
    Rng rng(1061);
    for (int iter = 0; iter < 3; ++iter) {
        vector<int> pool(497);
        iota(pool.begin(), pool.end(), 3);
        rng.shuffle(pool);
        vector<int> coins(pool.begin(), pool.begin() + 12);
        int amount = rng(9000, 10000);
        run(coins, amount, bfs(coins, amount));
    }
}

}
