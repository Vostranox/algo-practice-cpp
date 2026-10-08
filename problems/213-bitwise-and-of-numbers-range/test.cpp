#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static int and_loop(int left, int right) {
    int64_t res = -1;
    for (int64_t v = left; v <= right; ++v) {
        res &= v;
    }
    return static_cast<int>(res);
}

static int and_bits(int left, int right) {
    int64_t res = 0;
    for (int b = 0; b < 31; ++b) {
        int64_t bit = int64_t{1} << b;
        if ((left & bit) && (static_cast<int64_t>(left) | (bit - 1)) + 1 > right) {
            res |= bit;
        }
    }
    return static_cast<int>(res);
}

static void run(int left, int right, int want) {
    check(Solution().rangeBitwiseAnd(left, right), want, "left", left, "right", right);
}
static void run(int left, int right) {
    run(left, right, right - static_cast<int64_t>(left) <= 2000 ? and_loop(left, right) : and_bits(left, right));
}

TEST(examples) {
    run(12, 15, 12);
    run(26, 30, 24);
    run(9, 9, 9);
}

TEST(edge_cases) {
    run(0, 0, 0);
    run(0, 1, 0);
    run(1, 1, 1);
    run(1, 2, 0);
    run(2, 3, 2);
    run(5, 7, 4);
    run(4, 7, 4);
    run(7, 8, 0);
    run(8, 15, 8);
    run(16, 32, 0);
    run(1000, 1023, 992);
    run(INT_MAX, INT_MAX, INT_MAX);
    run(INT_MAX - 1, INT_MAX, INT_MAX - 1);
    run(0, INT_MAX, 0);
    run(1, INT_MAX, 0);
    run(1 << 30, (1 << 30) + 1, 1 << 30);
    run((1 << 30) - 1, 1 << 30, 0);
}

TEST(random) {
    Rng rng(201);
    for (int k = 0; k < 20000; ++k) {
        int left = rng(0, INT_MAX);
        run(left, static_cast<int>(min<int64_t>(INT_MAX, left + rng(0, 2000))));
    }
    for (int k = 0; k < 20000; ++k) {
        int a = rng(0, INT_MAX), b = rng(0, INT_MAX);
        run(min(a, b), max(a, b));
    }
    for (int k = 0; k < 20000; ++k) {
        int prefix_bits = rng(1, 30), low_bits = 31 - prefix_bits;
        int prefix = rng(1, (1 << prefix_bits) - 1) << low_bits;
        int a = prefix | rng(0, (1 << low_bits) - 1), b = prefix | rng(0, (1 << low_bits) - 1);
        run(min(a, b), max(a, b));
    }
}

TEST(large) {
    const int top = 1 << 30;
    for (int k = 0; k < 40; ++k) {
        run(top + k * 1000, INT_MAX - k * 1000, top);
    }
    run(top + (1 << 29), INT_MAX, top + (1 << 29));
    run(top + 12345, top + (1 << 29) + 54321, top);
}

}
