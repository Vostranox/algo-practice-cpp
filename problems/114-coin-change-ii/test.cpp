#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int amount, vector<int> coins, int want) {
    vector<int> arg = coins;
    check(Solution().change(amount, arg), want, "amount", amount, "coins", coins);
}

static int brute(int amount, const vector<int>& coins, size_t i = 0) {
    if (i == coins.size()) return amount == 0;
    int count = 0;
    for (int k = 0; k * coins[i] <= amount; ++k) {
        count += brute(amount - k * coins[i], coins, i + 1);
    }
    return count;
}

static vector<int64_t> table(int amount, const vector<int>& coins) {
    const int64_t CAP = int64_t{1} << 40;
    vector<vector<int64_t>> ways{vector<int64_t>(amount + 1, 0)};
    ways[0][0] = 1;
    for (int c : coins) {
        const vector<int64_t>& prev = ways.back();
        vector<int64_t> row = prev;
        for (int a = c; a <= amount; ++a) {
            row[a] = min(CAP, prev[a] + row[a - c]);
        }
        ways.push_back(row);
    }
    return ways.back();
}

static void random_case(Rng& rng, int amount, int count, int lo) {
    while (true) {
        vector<int> pool(5000 - lo + 1);
        iota(pool.begin(), pool.end(), lo);
        rng.shuffle(pool);
        vector<int> coins(pool.begin(), pool.begin() + count);
        vector<int64_t> ways = table(amount, coins);
        if (*max_element(ways.begin(), ways.end()) > INT_MAX) continue;
        run(amount, coins, static_cast<int>(ways[amount]));
        return;
    }
}

TEST(examples) {
    run(6, {1, 3, 4}, 4);
    run(7, {2, 4}, 0);
    run(0, {5}, 1);
}

TEST(edge_cases) {
    run(1, {1}, 1);
    run(10, {10}, 1);
    run(3, {2}, 0);
    run(5, {1, 2, 5}, 4);
    run(4, {3, 1}, 2);
    run(100, {1}, 1);
    run(5, {7}, 0);
    run(0, {1, 2, 3}, 1);
}

TEST(random) {
    Rng rng(1140);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> pool(12);
        iota(pool.begin(), pool.end(), 1);
        rng.shuffle(pool);
        vector<int> coins(pool.begin(), pool.begin() + rng(1, 4));
        int amount = rng(0, 30);
        run(amount, coins, brute(amount, coins));
    }
}

TEST(large) {
    run(5000, {1, 2}, 2501);
    run(5000, {3, 1, 2}, 2085834);
    int64_t ways125 = 0;
    for (int k = 0; k <= 1000; ++k) {
        ways125 += (5000 - 5 * k) / 2 + 1;
    }
    run(5000, {5, 2, 1}, static_cast<int>(ways125));
    run(5000, {1, 2, 3, 4}, static_cast<int>(table(5000, {1, 2, 3, 4})[5000]));
    run(4999, {2, 4, 6, 8}, 0);
    Rng rng(1141);
    random_case(rng, 5000, 300, 200);
    random_case(rng, 5000, 60, 30);
    random_case(rng, 5000, 40, 1);
}

TEST(big_intermediate_counts) {
    vector<int> evens;
    for (int k = 1; k <= 300; ++k) {
        evens.push_back(2 * k);
    }
    run(4999, evens, 0);
    evens.pop_back();
    evens.push_back(4999);
    run(4999, evens, 1);
}

}
