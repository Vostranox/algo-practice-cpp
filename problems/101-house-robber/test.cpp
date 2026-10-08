#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().rob(arg), want, "nums", nums);
}

static int brute(const vector<int>& nums) {
    int n = nums.size(), best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (mask & (mask >> 1)) continue;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {
                total += nums[i];
            }
        }
        best = max(best, total);
    }
    return best;
}

static int two_state(const vector<int>& nums) {
    int take = 0, skip = 0;
    for (int x : nums) {
        int newTake = skip + x;
        skip = max(take, skip);
        take = newTake;
    }
    return max(take, skip);
}

TEST(examples) {
    run({5, 1, 1, 5}, 10);
    run({3, 10, 3, 1, 2}, 12);
    run({4}, 4);
}

TEST(edge_cases) {
    run({0}, 0);
    run({2, 1}, 2);
    run({1, 2}, 2);
    run({0, 0, 0}, 0);
    run({2, 1, 1, 2}, 4);
    run({1, 3, 1}, 3);
    run({400, 0, 0, 400}, 800);
}

TEST(random) {
    Rng rng(1010);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> nums = rng.ints(rng(1, 14), 0, 30);
        run(nums, brute(nums));
    }
}

TEST(large) {
    run(vector<int>(100, 400), 400 * 50);
    run(vector<int>(99, 400), 400 * 50);
    vector<int> alternating;
    for (int i = 0; i < 50; ++i) {
        alternating.insert(alternating.end(), {0, 400});
    }
    run(alternating, 400 * 50);
    Rng rng(1011);
    for (int iter = 0; iter < 5; ++iter) {
        vector<int> nums = rng.ints(100, 0, 400);
        run(nums, two_state(nums));
    }
}

}
