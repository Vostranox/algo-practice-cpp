#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static bool happy(int n) {
    set<int> seen;
    while (n != 1 && !seen.count(n)) {
        seen.insert(n);
        string digits = to_string(n);
        n = 0;
        for (char c : digits) {
            n += (c - '0') * (c - '0');
        }
    }
    return n == 1;
}

static void run(int n, bool want) { check(Solution().isHappy(n), want, "n", n); }
static void run(int n) { run(n, happy(n)); }

TEST(examples) {
    run(7, true);
    run(4, false);
    run(100, true);
}

TEST(edge_cases) {
    run(1, true);
    run(2, false);
    run(10, true);
    run(1000000000, true);
    run(INT_MAX, false);
    run(89, false);
    run(145, false);
    run(3, false);
}

TEST(up_to_100) {
    const set<int> happy_numbers = {1, 7, 10, 13, 19, 23, 28, 31, 32, 44, 49, 68, 70, 79, 82, 86, 91, 94, 97, 100};
    for (int n = 1; n <= 100; ++n) {
        run(n, happy_numbers.count(n) > 0);
    }
}

TEST(random) {
    Rng rng(202);
    for (int n = 101; n < 3000; ++n) {
        run(n);
    }
    for (int k = 0; k < 3000; ++k) {
        run(rng(1, INT_MAX));
    }
}

}
