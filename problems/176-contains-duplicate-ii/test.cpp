#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int k, bool want) {
    vector<int> arg = nums;
    check(Solution().containsNearbyDuplicate(arg, k), want, "nums", nums, "k", k);
}

static bool brute(const vector<int>& nums, int k) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] == nums[j] && j - i <= k) return true;
        }
    }
    return false;
}

TEST(examples) {
    run({4, 1, 7, 4}, 3, true);
    run({4, 1, 7, 4}, 2, false);
    run({6, 3, 3}, 1, true);
}

TEST(edge_cases) {
    run({1}, 0, false);
    run({1}, 5, false);
    run({1, 1}, 0, false);
    run({1, 1}, 1, true);
    run({1, 2, 3, 1, 2, 1}, 2, true);
    run({5, 0, 5, 0, 5}, 1, false);
    run({5, 0, 5, 0, 5}, 2, true);
    run({1, 2, 3, 4, 5, 1}, 5, true);
    run({1, 2, 3, 4, 5, 1}, 4, false);
    run({-1000000000, 1000000000, -1000000000}, 2, true);
    run({-1000000000, 1000000000, -1000000000}, 1, false);
    run({7, 7, 7, 7}, 100000, true);
    run({1, 2, 3, 4}, 100000, false);
}

TEST(random) {
    Rng rng(219);
    for (int it = 0; it < 1000; ++it) {
        vector<int> nums = rng.ints(rng(1, 15), 0, rng(1, 10));
        int k = rng(0, 8);
        run(nums, k, brute(nums, k));
    }
}

TEST(large) {
    Rng rng(21900);
    const int n = 100000;
    vector<int> distinct(n);
    for (int i = 0; i < n; ++i) {
        distinct[i] = -1000000000 + 20000 * i;
    }
    rng.shuffle(distinct);
    run(distinct, 100000, false);
    run(distinct, 99999, false);
    vector<int> pair = distinct;
    pair[n - 1] = pair[n - 1 - 50000];
    run(pair, 50000, true);
    run(pair, 49999, false);
    vector<int> cyclic(n);
    for (int i = 0; i < n; ++i) {
        cyclic[i] = i % 1000;
    }
    run(cyclic, 999, false);
    run(cyclic, 1000, true);
}

}
