#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& piles, int h, int want) {
    vector<int> arg = piles;
    check(Solution().minEatingSpeed(arg, h), want, "piles", piles, "h", h);
}

static int64_t hours(const vector<int>& piles, int64_t k) {
    int64_t total = 0;
    for (int p : piles) {
        total += (p + k - 1) / k;
    }
    return total;
}

static int brute(const vector<int>& piles, int h) {
    int k = 1;
    while (hours(piles, k) > h) {
        ++k;
    }
    return k;
}

TEST(examples) {
    run({4, 9, 6}, 6, 4);
    run({10, 1, 25}, 3, 25);
    run({100}, 9, 12);
}

TEST(edge_cases) {
    run({1}, 1, 1);
    run({7}, 7, 1);
    run({7}, 100, 1);
    run({7}, 3, 3);
    run({3, 3, 3}, 3, 3);
    run({3, 3, 3}, 6, 2);
    run({3, 3, 3}, 8, 2);
    run({3, 3, 3}, 9, 1);
    run({5, 5, 5, 5}, 8, 3);
    run({1, 1, 1, 1000000000}, 4, 1000000000);
    run({1000000000}, 1, 1000000000);
    run({1000000000}, 2, 500000000);
    run({1000000000}, 3, 333333334);
}

TEST(random) {
    Rng rng(30);
    for (int iter = 0; iter < 3000; ++iter) {
        vector<int> piles = rng.ints(rng(1, 8), 1, 40);
        int total = accumulate(piles.begin(), piles.end(), 0);
        int h = rng(static_cast<int>(piles.size()), total + 3);
        run(piles, h, brute(piles, h));
    }
}

TEST(large) {
    const int n = 10000;
    run({1000000000}, 1000000000, 1);
    run(vector<int>(n, 1000000000), n, 1000000000);
    run(vector<int>(n, 1000000000), 2 * n, 500000000);
    run(vector<int>(n, 1000000000), 1000000000, 10000);
    Rng rng(875);
    for (int iter = 0; iter < 5; ++iter) {
        vector<int> piles = rng.ints(n, 1, 1000000000), arg = piles;
        int h = rng(n, 1000000000);
        int got = Solution().minEatingSpeed(arg, h);
        int64_t at = got >= 1 ? hours(piles, got) : -1, below = got > 1 ? hours(piles, got - 1) : -1;
        ensure(got >= 1 && at <= h, "too slow: Koko does not finish within h hours at this speed",
               "piles", piles, "h", h, "got", got, "hours needed", at);
        ensure(got == 1 || below > h, "not the minimum: speed got - 1 also finishes in time",
               "piles", piles, "h", h, "got", got, "hours at got - 1", below);
    }
}

}
