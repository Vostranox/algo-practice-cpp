#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(double x, int n, double want) { check_close(Solution().myPow(x, n), want, "x", x, "n", n); }
static void run(double x, int n) { run(x, n, std::pow(x, n)); }

TEST(examples) {
    run(3.0, 4, 81.0);
    run(1.5, 3, 3.375);
    run(2.0, -3, 0.125);
}

TEST(edge_cases) {
    run(5.5, 0, 1.0);
    run(-3.0, 0, 1.0);
    run(0.0, 1, 0.0);
    run(0.0, 7, 0.0);
    run(7.25, 1, 7.25);
    run(4.0, -1, 0.25);
    run(-2.0, 3, -8.0);
    run(-2.0, 4, 16.0);
    run(-0.5, -3, -8.0);
    run(-0.5, -4, 16.0);
    run(10.0, 4, 10000.0);
    run(0.1, -4);
    run(-99.9, 2);
    run(99.99, -2);
    run(2.0, -30);
    run(1.1, 25);
    run(0.9, -50);
}

TEST(extreme_exponents) {
    run(1.0, INT_MIN, 1.0);
    run(-1.0, INT_MIN, 1.0);
    run(-1.0, INT_MAX, -1.0);
    run(2.0, INT_MIN, 0.0);
    run(0.5, INT_MAX, 0.0);
    run(0.0, INT_MAX, 0.0);
}

TEST(large) {
    run(1.000000001, INT_MAX);
    run(0.999999999, INT_MAX);
    run(1.0000000005, INT_MIN);
    run(0.9999999995, INT_MIN);
    run(-1.000000001, INT_MAX);
    run(-1.000000001, INT_MAX - 1);
    run(-0.999999999, INT_MIN);
    run(1.000000002, INT_MAX - 1);
    run(0.999999998, INT_MIN + 1);
    run(1.000000004, INT_MAX);
    run(0.999999996, INT_MIN);
    run(-1.000000003, INT_MAX);
    run(-1.0000000015, INT_MIN + 1);
    run(1.0000000025, INT_MIN);
}

}
