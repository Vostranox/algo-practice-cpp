#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().maxSubArray(arg), want, "nums", nums);
}

static int brute(const vector<int>& nums) {
    int best = INT_MIN;
    for (size_t i = 0; i < nums.size(); ++i) {
        int sum = 0;
        for (size_t j = i; j < nums.size(); ++j) {
            best = max(best, sum += nums[j]);
        }
    }
    return best;
}

TEST(examples) {
    run({3, -5, 4, -1, 2, 1, -6, 2}, 6);
    run({-3, -1, -2}, -1);
    run({5, -2, 7}, 10);
}

TEST(edge_cases) {
    run({1}, 1);
    run({-7}, -7);
    run({0}, 0);
    run({-1, 0, -2}, 0);
    run({2, -1, 2}, 3);
    run({2, -3, 2}, 2);
    run({-5, 4, 6}, 10);
    run({4, 6, -20, 3}, 10);
    run({-2, -2, -1, -2}, -1);
    run(vector<int>(5, -10000), -10000);
    run(vector<int>(5, 10000), 50000);
}

TEST(random) {
    Rng rng(122);
    for (int it = 0; it < 500; ++it) {
        vector<int> nums = rng.ints(rng(1, 12), -10, 10);
        run(nums, brute(nums));
    }
}

TEST(large) {
    const int n = 100000;
    Rng rng(53);
    vector<int> nums = rng.ints(n, -10000, -1);
    run(nums, *max_element(nums.begin(), nums.end()));
    nums = rng.ints(n, 1, 10000);
    run(nums, static_cast<int>(accumulate(nums.begin(), nums.end(), int64_t{0})));
    nums.assign(n, -10000);
    fill(nums.begin() + 40000, nums.begin() + 41000, 10000);
    run(nums, 10000000);
    nums = rng.ints(n, -10000, 9000);
    int64_t best = INT64_MIN, lowest = 0, prefix = 0;
    for (int x : nums) {
        prefix += x;
        best = max(best, prefix - lowest);
        lowest = min(lowest, prefix);
    }
    run(nums, static_cast<int>(best));
}

}
