#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int want) {
    vector<int> arg = nums;
    check(Solution().missingNumber(arg), want, "nums", nums);
}

static vector<int> make(Rng& rng, int n, int missing) {
    vector<int> nums;
    for (int v = 0; v <= n; ++v) {
        if (v != missing) {
            nums.push_back(v);
        }
    }
    rng.shuffle(nums);
    return nums;
}

TEST(examples) {
    run({4, 2, 0, 1}, 3);
    run({1, 0}, 2);
    run({1}, 0);
}

TEST(edge_cases) {
    run({0}, 1);
    run({2, 0}, 1);
    run({0, 1}, 2);
    run({2, 1}, 0);
    run({3, 0, 1}, 2);
    run({5, 4, 3, 2, 1}, 0);
    run({0, 1, 2, 3, 4}, 5);
    run({1, 2, 3, 4, 5, 0, 7}, 6);
}

TEST(large) {
    Rng rng(268);
    const int n = 10000;
    for (int missing : {0, n, rng(1, n - 1)}) {
        run(make(rng, n, missing), missing);
    }
}

TEST(random) {
    Rng rng(2680);
    for (int k = 0; k < 1000; ++k) {
        int n = rng(1, 50), missing = rng(0, n);
        run(make(rng, n, missing), missing);
    }
}

}
