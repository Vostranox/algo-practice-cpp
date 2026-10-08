#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int n, const vector<int>& want) {
    vector<int> got = Solution().countBits(n);
    ensure(got.size() == want.size(), "the answer must have length n + 1 = " + to_string(n + 1),
           "n", n, "got length", got.size());
    for (int i = 0; i <= n; ++i) {
        if (got[i] != want[i]) {
            ensure(false, "wrong value at index " + to_string(i), "n", n, "index", i,
                   "binary", bitset<17>(i).to_string(), "expected", want[i], "got", got[i]);
        }
    }
    check(got, want, "n", n);
}

static void run(int n) {
    vector<int> want;
    for (int i = 0; i <= n; ++i) {
        want.push_back(static_cast<int>(bitset<32>(i).count()));
    }
    run(n, want);
}

TEST(examples) {
    run(3, {0, 1, 1, 2});
    run(6, {0, 1, 1, 2, 1, 2, 2});
    run(0, {0});
}

TEST(edge_cases) {
    run(1, {0, 1});
    run(2, {0, 1, 1});
    run(8, {0, 1, 1, 2, 1, 2, 2, 3, 1});
    run(16, {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1});
    for (int n : {15, 31, 32, 63, 64, 100}) {
        run(n);
    }
}

TEST(large) {
    run(100000);
    run(65535);
    run(65536);
}

}
