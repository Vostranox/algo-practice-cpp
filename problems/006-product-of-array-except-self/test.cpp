#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, vector<int> want) {
    vector<int> arg = nums;
    check(Solution().productExceptSelf(arg), want, "nums", nums);
}

static vector<int> brute(const vector<int>& nums) {
    vector<int> res;
    for (size_t i = 0; i < nums.size(); ++i) {
        int64_t p = 1;
        for (size_t j = 0; j < nums.size(); ++j) {
            if (j != i) {
                p *= nums[j];
            }
        }
        res.push_back(static_cast<int>(p));
    }
    return res;
}

TEST(examples) {
    run({2, 3, 4, 5}, {60, 40, 30, 24});
    run({-2, 0, 5, 3}, {0, -30, 0, 0});
    run({1, -1}, {-1, 1});
}

TEST(edge_cases) {
    run({0, 4}, {4, 0});
    run({0, 0}, {0, 0});
    run({3, 0, 2, 0}, {0, 0, 0, 0});
    run({1, 2, 0, 4}, {0, 0, 8, 0});
    run({30, -30}, {-30, 30});
    run({-1, -1, -1}, {1, 1, 1});
    run({7, 7, 7, 7}, {343, 343, 343, 343});
    run({-2, 3, -4, 5, 1}, {-60, 40, -30, 24, 120});
}

TEST(random) {
    Rng rng(6);
    for (int i = 0; i < 300; ++i) {
        vector<int> nums = rng.ints(rng(2, 9), -5, 5);
        run(nums, brute(nums));
    }
}

TEST(large) {
    Rng rng(66);
    const int n = 100000;
    vector<int> nums(n);
    for (int& x : nums) {
        x = rng.coin() ? 1 : -1;
    }
    for (int placed = 0; placed < 30;) {
        int i = rng(0, n - 1);
        if (nums[i] != 2) {
            nums[i] = 2, ++placed;
        }
    }
    int64_t total = 1;
    for (int x : nums) {
        total *= x;
    }
    vector<int> want(n);
    for (int i = 0; i < n; ++i) {
        want[i] = static_cast<int>(total / nums[i]);
    }
    run(nums, want);
    const int z = 54321;
    want.assign(n, 0);
    want[z] = static_cast<int>(total / nums[z]);
    nums[z] = 0;
    run(nums, want);
    nums[7] = 0;
    run(nums, vector<int>(n, 0));
}

}
