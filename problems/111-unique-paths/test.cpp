#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int m, int n, int want) {
    check(Solution().uniquePaths(m, n), want, "m", m, "n", n);
}

static int brute(int m, int n, int r = 0, int c = 0) {
    if (r == m - 1 && c == n - 1) return 1;
    return (r + 1 < m ? brute(m, n, r + 1, c) : 0) + (c + 1 < n ? brute(m, n, r, c + 1) : 0);
}

static int64_t binom(int a, int b) {
    int64_t c = 1;
    for (int i = 1; i <= b; ++i) {
        c = c * (a - b + i) / i;
    }
    return c;
}

TEST(examples) {
    run(3, 3, 6);
    run(2, 4, 4);
    run(1, 7, 1);
}

TEST(edge_cases) {
    run(1, 1, 1);
    run(2, 2, 2);
    run(100, 1, 1);
    run(1, 100, 1);
    run(2, 100, 100);
    run(3, 7, 28);
    run(7, 3, 28);
}

TEST(random) {
    for (int m = 1; m <= 9; ++m) {
        for (int n = 1; n <= 9; ++n) {
            run(m, n, brute(m, n));
        }
    }
}

TEST(large) {
    for (auto [m, n] : vector<pair<int, int>>{{16, 20}, {20, 16}, {17, 18}, {18, 17}, {100, 3}, {10, 30}}) {
        run(m, n, static_cast<int>(binom(m + n - 2, m - 1)));
    }
}

}
