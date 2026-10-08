#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> cost, int want) {
    vector<int> arg = cost;
    check(Solution().minCostClimbingStairs(arg), want, "cost", cost);
}

static int brute(const vector<int>& cost, int i) {
    if (i >= static_cast<int>(cost.size())) return 0;
    return cost[i] + min(brute(cost, i + 1), brute(cost, i + 2));
}

static int forward(const vector<int>& cost) {
    int n = cost.size();
    vector<int> best(n + 1, INT_MAX);
    best[0] = best[1] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j : {i + 1, i + 2}) {
            if (j <= n) {
                best[j] = min(best[j], best[i] + cost[i]);
            }
        }
    }
    return best[n];
}

TEST(examples) {
    run({4, 9, 2}, 6);
    run({3, 1, 3, 1, 3, 1, 3}, 3);
    run({10, 15}, 10);
}

TEST(edge_cases) {
    run({0, 0}, 0);
    run({5, 0}, 0);
    run({0, 5}, 0);
    run({7, 7}, 7);
    run({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}, 6);
    run({999, 999, 999}, 999);
}

TEST(random) {
    Rng rng(100);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> cost = rng.ints(rng(2, 14), 0, 20);
        run(cost, min(brute(cost, 0), brute(cost, 1)));
    }
}

TEST(large) {
    run(vector<int>(1000, 999), 999 * 500);
    run(vector<int>(999, 999), 999 * 499);
    vector<int> alternating;
    for (int i = 0; i < 500; ++i) {
        alternating.insert(alternating.end(), {0, 999});
    }
    run(alternating, 0);
    Rng rng(101);
    for (int iter = 0; iter < 3; ++iter) {
        vector<int> cost = rng.ints(1000, 0, 999);
        run(cost, forward(cost));
    }
}

}
