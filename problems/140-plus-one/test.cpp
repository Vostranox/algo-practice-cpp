#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& digits, const vector<int>& want) {
    vector<int> arg = digits;
    check(Solution().plusOne(arg), want, "digits", digits);
}

TEST(examples) {
    run({4, 5, 9}, {4, 6, 0});
    run({9, 9}, {1, 0, 0});
    run({0}, {1});
}

TEST(all_nines) {
    run({9}, {1, 0});
    run({9, 9, 9}, {1, 0, 0, 0});
    vector<int> want(101, 0);
    want[0] = 1;
    run(vector<int>(100, 9), want);
    run({8, 9, 9}, {9, 0, 0});
    run({1, 0, 0, 9, 9}, {1, 0, 1, 0, 0});
}

TEST(edge_cases) {
    run({1}, {2});
    run({8}, {9});
    run({1, 0}, {1, 1});
    run({2, 0, 0, 0}, {2, 0, 0, 1});
    run({9, 0, 9}, {9, 1, 0});
    vector<int> ones(100, 1), ones_plus = ones;
    ones_plus.back() = 2;
    run(ones, ones_plus);
    vector<int> nines_8(100, 9), nines(100, 9);
    nines_8.back() = 8;
    run(nines_8, nines);
}

TEST(random) {
    Rng rng(66);
    for (int t = 0; t < 2000; ++t) {
        int k = rng(0, 20), len = rng(k + 1, 100);
        vector<int> digits, want;
        for (int i = 0; i < len - k - 1; ++i) {
            int d = i == 0 ? rng(1, 9) : rng(0, 9);
            digits.push_back(d);
            want.push_back(d);
        }
        int d = rng(digits.empty() && len > 1 ? 1 : 0, 8);
        digits.push_back(d);
        want.push_back(d + 1);
        for (int i = 0; i < k; ++i) {
            digits.push_back(9);
            want.push_back(0);
        }
        run(digits, want);
    }
}

}
