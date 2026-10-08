#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int k, int w, vector<int> profits, vector<int> capital, int want) {
    vector<int> p = profits, c = capital;
    check(Solution().findMaximizedCapital(k, w, p, c), want, "k", k, "w", w, "profits", profits, "capital", capital);
}

static int64_t best_exhaustive(int k, int64_t w, const vector<int>& profits, const vector<int>& capital,
                                 vector<bool>& used) {
    int64_t best = w;
    if (k == 0) return best;
    for (size_t i = 0; i < profits.size(); ++i) {
        if (!used[i] && capital[i] <= w) {
            used[i] = true;
            best = max(best, best_exhaustive(k - 1, w + profits[i], profits, capital, used));
            used[i] = false;
        }
    }
    return best;
}

static int64_t greedy_scan(int k, int64_t w, const vector<int>& profits, const vector<int>& capital) {
    vector<bool> used(profits.size());
    for (int round = 0; round < k; ++round) {
        int pick = -1;
        for (int i = 0; i < static_cast<int>(profits.size()); ++i) {
            if (!used[i] && capital[i] <= w && (pick < 0 || profits[i] > profits[pick])) {
                pick = i;
            }
        }
        if (pick < 0) break;
        used[pick] = true;
        w += profits[pick];
    }
    return w;
}

TEST(examples) {
    run(2, 1, {3, 5, 2, 10}, {0, 2, 1, 5}, 9);
    run(3, 0, {4, 1, 6}, {1, 0, 6}, 5);
    run(1, 2, {5, 3}, {3, 2}, 5);
}

TEST(edge_cases) {
    run(1, 0, {1}, {0}, 1);
    run(1, 0, {1}, {1}, 0);
    run(5, 0, {1, 2, 3}, {0, 0, 0}, 6);
    run(2, 0, {0, 5}, {0, 1}, 0);
    run(3, 0, {1, 1, 1}, {2, 1, 0}, 3);
    run(2, 0, {1, 2, 10}, {0, 0, 2}, 12);
    run(2, 0, {5, 5, 5}, {0, 0, 0}, 10);
    run(1, 1000000000, {10000}, {1000000000}, 1000010000);
    run(3, 7, {2, 9, 4, 6}, {7, 8, 9, 30}, 22);
    run(100000, 5, {1, 1}, {6, 7}, 5);
}

TEST(random_small) {
    Rng rng(502);
    for (int t = 0; t < 1500; ++t) {
        int n = rng(1, 7), k = rng(1, n + 1), w = rng(0, 6);
        vector<int> profits = rng.ints(n, 0, 6), capital = rng.ints(n, 0, 12);
        vector<bool> used(n);
        run(k, w, profits, capital, best_exhaustive(k, w, profits, capital, used));
    }
}

TEST(random_medium) {
    Rng rng(5020);
    for (int t = 0; t < 200; ++t) {
        int n = rng(1, 300), k = rng(1, n + 5), w = rng(0, 1000);
        vector<int> profits = rng.ints(n, 0, rng(0, 1) ? 50 : 10000);
        vector<int> capital = rng.ints(n, 0, rng(0, 1) ? 3000 : 1000000000);
        run(k, w, profits, capital, greedy_scan(k, w, profits, capital));
    }
}

TEST(large) {
    const int n = 100000;
    Rng rng(50200);
    {
        vector<int> profits = rng.ints(n, 0, 10000), capital(n, 0);
        int64_t sum = accumulate(profits.begin(), profits.end(), int64_t{0});
        run(n, 1000000000, profits, capital, 1000000000 + sum);
    }
    {
        vector<int> profits = rng.ints(n, 0, 10000), capital = rng.ints(n, 0, 1000000000);
        vector<int> desc = sorted(profits);
        reverse(desc.begin(), desc.end());
        run(n / 2, 1000000000, profits, capital, 1000000000 + accumulate(desc.begin(), desc.begin() + n / 2, int64_t{0}));
    }
    {
        vector<int> capital(n);
        iota(capital.begin(), capital.end(), 0);
        rng.shuffle(capital);
        run(n, 0, vector<int>(n, 1), capital, n);
    }
    {
        vector<int> profits = rng.ints(n, 0, 10000), capital(n);
        int64_t sum = 0;
        for (int i = 0; i < n; ++i) {
            capital[i] = i % 2 ? 0 : rng(500000001, 1000000000);
            if (i % 2) {
                sum += profits[i];
            }
        }
        run(n, 0, profits, capital, sum);
    }
}

}
