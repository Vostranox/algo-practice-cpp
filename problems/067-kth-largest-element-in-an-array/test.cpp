#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int k, int want) {
    vector<int> arg = nums;
    check(Solution().findKthLargest(arg, k), want, "nums", nums, "k", k);
}

TEST(examples) {
    run({7, 2, 9, 4, 1}, 2, 7);
    run({6, 3, 6, 6, 2, 8}, 3, 6);
    run({-4}, 1, -4);
}

TEST(edge_cases) {
    run({5, 5, 3}, 2, 5);
    run({5, 5, 3}, 3, 3);
    run({3, 1, 2}, 1, 3);
    run({3, 1, 2}, 3, 1);
    run({-10000, 10000}, 1, 10000);
    run({-10000, 10000}, 2, -10000);
    run({-1, -1, -1, -1}, 3, -1);
    run({1, 2, 3, 4, 5, 6}, 4, 3);
    run({2, 1, 2, 1, 2, 1, 2}, 4, 2);
    run({2, 1, 2, 1, 2, 1, 2}, 5, 1);
}

TEST(random) {
    Rng rng(215);
    for (int iter = 0; iter < 2000; ++iter) {
        int n = rng(1, 30);
        vector<int> nums = rng.ints(n, -15, 15);
        int k = rng(1, n);
        vector<int> desc = sorted(nums);
        reverse(desc.begin(), desc.end());
        run(nums, k, desc[k - 1]);
    }
}

TEST(large) {
    vector<int> base;
    for (int v = -10000; v < 10000; ++v) {
        base.insert(base.end(), 5, v);
    }
    auto want = [](int k) { return 9999 - (k - 1) / 5; };
    Rng rng(2150);
    vector<int> shuffled = base;
    rng.shuffle(shuffled);
    for (int k : {1, 31337, 50000, 100000}) {
        run(shuffled, k, want(k));
    }
    run(base, 50000, want(50000));
    vector<int> desc(base.rbegin(), base.rend());
    run(desc, 70001, want(70001));
    for (int k : {1, 54321, 100000}) {
        run(vector<int>(100000, 7), k, 7);
    }
}

}
