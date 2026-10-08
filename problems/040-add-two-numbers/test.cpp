#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> a, vector<int> b, vector<int> want) {
    ListNode* got = Solution().addTwoNumbers(build_list(a), build_list(b));
    check(list_to_vec(got), want, "l1", a, "l2", b);
}

static vector<int> digits(uint64_t x) {
    vector<int> d;
    do {
        d.push_back(x % 10);
        x /= 10;
    } while (x);
    return d;
}

TEST(examples) {
    run({5, 0, 3}, {8, 9}, {3, 0, 4});
    run({0}, {0}, {0});
    run({9, 9, 9}, {1}, {0, 0, 0, 1});
}

TEST(edge_cases) {
    run({0}, {7, 3}, {7, 3});
    run({1}, {9, 9, 9, 9}, {0, 0, 0, 0, 1});
    run({5}, {5}, {0, 1});
    run({2, 4, 6}, {3, 5, 2}, {5, 9, 8});
    run({9, 9}, {9, 9}, {8, 9, 1});
}

TEST(random_small) {
    Rng rng(2);
    for (int i = 0; i < 2000; ++i) {
        uint64_t x = rng.range(0, rng.coin() ? 999 : int64_t{4000000000000000000});
        uint64_t y = rng.range(0, rng.coin() ? 999 : int64_t{4000000000000000000});
        run(digits(x), digits(y), digits(x + y));
    }
}

TEST(long_numbers) {
    Rng rng(20);
    for (int t = 0; t < 200; ++t) {
        int k = rng(1, 100);
        vector<int> x = rng.ints(k, 0, 9);
        if (k > 1 && x.back() == 0) {
            x.back() = rng(1, 8);
        }
        vector<int> y(k);
        for (int i = 0; i < k; ++i) {
            y[i] = 9 - x[i];
        }
        while (y.size() > 1 && y.back() == 0) {
            y.pop_back();
        }
        run(x, y, vector<int>(k, 9));
        if (x[0] < 9) {
            vector<int> x1 = x;
            ++x1[0];
            vector<int> want(k, 0);
            want.push_back(1);
            run(x1, y, want);
        }
    }
}

}
