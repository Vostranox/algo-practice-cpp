#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static bool palindrome(int x) {
    string s = to_string(x);
    return equal(s.begin(), s.end(), s.rbegin());
}

static void run(int x, bool want) { check(Solution().isPalindrome(x), want, "x", x); }
static void run(int x) { run(x, palindrome(x)); }

static int64_t make_palindrome(Rng& rng, int len) {
    string half = rng.str(1, "123456789") + rng.str((len + 1) / 2 - 1, "0123456789");
    string s = half + string(half.rbegin() + len % 2, half.rend());
    int64_t v = stoll(s);
    return v > INT_MAX ? -1 : v;
}

TEST(examples) {
    run(1331, true);
    run(-44, false);
    run(120, false);
}

TEST(edge_cases) {
    run(0, true);
    run(7, true);
    run(-7, false);
    run(-1, false);
    run(11, true);
    run(12, false);
    run(101, true);
    run(1001, true);
    run(1221, true);
    run(1231, false);
    run(12321, true);
    run(123321, true);
    run(123421, false);
    run(-12321, false);
    run(1000021, false);
    run(1234567, false);
}

TEST(trailing_zeros) {
    run(10, false);
    run(20, false);
    run(100, false);
    run(110, false);
    run(1010, false);
    run(1100, false);
    run(10010, false);
    run(1000000000, false);
    run(2100000000, false);
}

TEST(ten_digits) {
    run(INT_MAX, false);
    run(1000000009, false);
    run(1999999999, false);
    run(1463847419, false);
    run(2147483642, false);
    run(INT_MIN, false);
    run(-2147447412, false);
    run(2147483641, false);
    run(1234564321, false);
    run(2147447412, true);
    run(1000000001, true);
    run(1999999991, true);
    run(1234554321, true);
    run(2000000002, true);
}

TEST(random) {
    Rng rng(9);
    for (int x = -1000; x <= 100000; ++x) {
        run(x);
    }
    for (int k = 0; k < 20000; ++k) {
        run(rng(INT_MIN, INT_MAX));
    }
    for (int k = 0; k < 20000; ++k) {
        int64_t p = make_palindrome(rng, rng(1, 10));
        if (p < 0) continue;
        run(static_cast<int>(p), true);
        if (p >= 10) {
            run(static_cast<int>(p - 1), palindrome(static_cast<int>(p - 1)));
            run(static_cast<int>(-p), false);
        }
    }
}

}
