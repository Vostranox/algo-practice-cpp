#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int k, const vector<int>& want) {
    vector<int> arg = nums;
    Solution().rotate(arg, k);
    check(arg, want, "nums", nums, "k", k);
}

static vector<int> rotated(const vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> out(n);
    for (int i = 0; i < n; ++i) {
        out[(i + k) % n] = nums[i];
    }
    return out;
}

static void run(const vector<int>& nums, int k) { run(nums, k, rotated(nums, k)); }

TEST(examples) {
    run({1, 2, 3, 4, 5, 6}, 2, {5, 6, 1, 2, 3, 4});
    run({10, -20, 30}, 4, {30, 10, -20});
    run({9, 8}, 0, {9, 8});
}

TEST(edge_cases) {
    run({5}, 0, {5});
    run({5}, 100000, {5});
    run({1, 2}, 1, {2, 1});
    run({1, 2}, 2, {1, 2});
    run({1, 2}, 3, {2, 1});
    run({1, 2, 3, 4, 5, 6}, 6, {1, 2, 3, 4, 5, 6});
    run({1, 2, 3, 4, 5, 6}, 3, {4, 5, 6, 1, 2, 3});
    run({1, 2, 3, 4, 5, 6}, 4, {3, 4, 5, 6, 1, 2});
    run({1, 2, 3, 4, 5, 6}, 13, {6, 1, 2, 3, 4, 5});
    run({1, 2, 3, 4}, 2, {3, 4, 1, 2});
    run({1, 2, 3, 4, 5, 6, 7}, 100000, {3, 4, 5, 6, 7, 1, 2});
    run({7, 7, 7, 8}, 1, {8, 7, 7, 7});
    run({INT_MIN, INT_MAX, 0}, 1, {0, INT_MIN, INT_MAX});
}

TEST(random) {
    Rng rng(189);
    for (int it = 0; it < 1000; ++it) {
        vector<int> nums = rng.ints(rng(1, 12), -9, 9);
        run(nums, rng(0, 30));
    }
}

TEST(large) {
    Rng rng(18900);
    vector<int> nums = rng.ints(100000, INT_MIN, INT_MAX);
    for (int k : {1, 99999, 100000, 77777}) {
        run(nums, k);
    }
    for (int i = 0; i < 30; ++i) {
        run(nums, rng(40000, 60000));
    }
}

}
