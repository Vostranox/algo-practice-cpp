#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int n, int want) {
    check(Solution().climbStairs(n), want, "n", n);
}

static int brute(int left) {
    if (left == 0) return 1;
    int total = 0;
    for (int step : {1, 2}) {
        if (step <= left) {
            total += brute(left - step);
        }
    }
    return total;
}

static int64_t by_formula(int n) {
    int64_t total = 0;
    for (int k = 0; 2 * k <= n; ++k) {
        int64_t c = 1;
        for (int i = 1; i <= k; ++i) {
            c = c * (n - 2 * k + i) / i;
        }
        total += c;
    }
    return total;
}

TEST(examples) {
    run(3, 3);
    run(5, 8);
    run(1, 1);
}

TEST(edge_cases) {
    run(2, 2);
    run(4, 5);
    run(10, 89);
}

TEST(random) {
    for (int n = 1; n <= 25; ++n) {
        run(n, brute(n));
    }
}

TEST(large) {
    for (int rep = 0; rep < 3; ++rep) {
        run(45, 1836311903);
    }
    for (int n = 44; n >= 30; --n) {
        run(n, static_cast<int>(by_formula(n)));
    }
}

}
