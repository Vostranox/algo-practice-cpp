#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static int reversed_int(int x) {
    string s = to_string(llabs(static_cast<int64_t>(x)));
    std::reverse(s.begin(), s.end());
    int64_t r = stoll(s) * (x < 0 ? -1 : 1);
    return r < INT_MIN || r > INT_MAX ? 0 : static_cast<int>(r);
}

static void run(int x, int want) { check(Solution().reverse(x), want, "x", x); }
static void run(int x) { run(x, reversed_int(x)); }

TEST(examples) {
    run(4560, 654);
    run(-317, -713);
    run(1000000009, 0);
}

TEST(edge_cases) {
    run(0, 0);
    run(7, 7);
    run(-8, -8);
    run(10, 1);
    run(-1000, -1);
    run(1200, 21);
    run(-2147483412, -2143847412);
    run(1463847412, 2147483641);
    run(-1463847412, -2147483641);
}

TEST(overflow) {
    run(INT_MAX, 0);
    run(INT_MIN, 0);
    run(1473847412, 0);
    run(-1473847412, 0);
    run(1563847412, 0);
    run(-1563847412, 0);
    run(1534236469, 0);
    run(-2000000003, 0);
    run(1999999999, 0);
    run(1000000003, 0);
}

TEST(random) {
    Rng rng(7);
    for (int k = 0; k < 20000; ++k) {
        run(rng(INT_MIN, INT_MAX));
    }
    for (int k = 0; k < 20000; ++k) {
        int lo = -static_cast<int>(std::pow(10, rng(1, 9))), hi = static_cast<int>(std::pow(10, rng(1, 9)));
        run(rng(lo, hi));
    }
}

}
