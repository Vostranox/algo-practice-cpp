#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int x, int want) { check(Solution().mySqrt(x), want, "x", x); }

static int oracle(int x) {
    int64_t r = static_cast<int64_t>(std::sqrt(static_cast<double>(x)));
    while (r * r > x) {
        --r;
    }
    while ((r + 1) * (r + 1) <= x) {
        ++r;
    }
    return static_cast<int>(r);
}

TEST(examples) {
    run(16, 4);
    run(27, 5);
    run(0, 0);
}

TEST(edge_cases) {
    run(1, 1);
    run(2, 1);
    run(3, 1);
    run(4, 2);
    run(8, 2);
    run(9, 3);
    run(99, 9);
    run(100, 10);
    run(1073741823, 32767);
    run(1073741824, 32768);
    run(2147395599, 46339);
    run(2147395600, 46340);
    run(2147395601, 46340);
    run(2147483646, 46340);
    run(2147483647, 46340);
}

TEST(around_squares) {
    for (int64_t r = 1; r <= 46340; ++r) {
        run(static_cast<int>(r * r - 1), static_cast<int>(r) - 1);
        run(static_cast<int>(r * r), static_cast<int>(r));
        if (r * r + 1 <= INT_MAX) {
            run(static_cast<int>(r * r + 1), static_cast<int>(r));
        }
    }
}

TEST(large) {
    Rng rng(69);
    for (int q = 0; q < 300000; ++q) {
        int x = q % 2 ? rng(1 << 30, INT_MAX) : rng(INT_MAX - 1000000, INT_MAX);
        int want = oracle(x), got = Solution().mySqrt(x);
        if (got != want) {
            check(got, want, "x", x);
        }
    }
    for (int q = 0; q < 10000; ++q) {
        int x = rng(0, INT_MAX);
        run(x, oracle(x));
    }
}

}
