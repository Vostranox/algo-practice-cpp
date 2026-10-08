#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int n, int want) { check(Solution().trailingZeroes(n), want, "n", n); }

TEST(examples) {
    run(4, 0);
    run(10, 2);
    run(25, 6);
}

TEST(edge_cases) {
    run(0, 0);
    run(1, 0);
    run(5, 1);
    run(9, 1);
    run(20, 4);
    run(21, 4);
    run(24, 4);
    run(26, 6);
    run(30, 7);
    run(99, 22);
    run(100, 24);
    run(124, 28);
    run(125, 31);
    run(624, 152);
    run(625, 156);
    run(3125, 781);
    run(9999, 2495);
    run(10000, 2499);
}

TEST(exact_factorials) {
    vector<int> digits = {1};
    for (int n = 0; n <= 400; ++n) {
        if (n > 0) {
            int carry = 0;
            for (int& d : digits) {
                int v = d * n + carry;
                d = v % 10;
                carry = v / 10;
            }
            for (; carry; carry /= 10) {
                digits.push_back(carry % 10);
            }
        }
        int zeros = 0;
        while (digits[zeros] == 0) {
            ++zeros;
        }
        run(n, zeros);
    }
}

TEST(all_n) {
    int fives = 0;
    for (int n = 0; n <= 10000; ++n) {
        for (int k = n; k > 0 && k % 5 == 0; k /= 5) {
            ++fives;
        }
        run(n, fives);
    }
}

}
