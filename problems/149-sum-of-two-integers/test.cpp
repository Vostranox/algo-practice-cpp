#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int a, int b) { check(Solution().getSum(a, b), a + b, "a", a, "b", b); }

TEST(examples) {
    run(3, 4);
    run(-6, 2);
    run(-5, -7);
}

TEST(edge_cases) {
    for (auto [a, b] : vector<pair<int, int>>{{0, 0}, {0, 5}, {5, 0}, {0, -5}, {-5, 0}, {1, -1}, {-1, 1}, {-1, -1},
                                              {1000, 1000}, {-1000, -1000}, {-1000, 1000}, {1000, -1000}, {999, 1},
                                              {-999, -1}, {512, 512}, {-512, -512}, {1000, -1}, {-1000, 1},
                                              {7, -8}, {-8, 7}}) {
        run(a, b);
    }
}

TEST(every_pair) {
    Solution sol;
    for (int a = -1000; a <= 1000; ++a) {
        for (int b = -1000; b <= 1000; ++b) {
            int got = sol.getSum(a, b);
            if (got != a + b) {
                check(got, a + b, "a", a, "b", b);
            }
        }
    }
}

}
