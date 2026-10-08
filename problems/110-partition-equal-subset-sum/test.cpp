#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, bool want) {
    vector<int> arg = nums;
    check(Solution().canPartition(arg), want, "nums", nums);
}

static bool brute(const vector<int>& nums) {
    int n = nums.size(), total = accumulate(nums.begin(), nums.end(), 0);
    for (int mask = 0; mask < (1 << n); ++mask) {
        int side = 0;
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {
                side += nums[i];
            }
        }
        if (2 * side == total) return true;
    }
    return false;
}

static bool bitset_oracle(const vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2) return false;
    bitset<20001> reach;
    reach[0] = 1;
    for (int x : nums) {
        reach |= reach << x;
    }
    return reach[total / 2];
}

TEST(examples) {
    run({3, 1, 5, 9, 4, 2}, true);
    run({2, 3, 7}, false);
    run({8}, false);
}

TEST(edge_cases) {
    run({1}, false);
    run({1, 1}, true);
    run({1, 2}, false);
    run({2, 2, 2}, false);
    run({100, 100}, true);
    run({1, 2, 3, 4, 5, 6, 7}, true);
    run({3, 3, 3, 4, 5}, true);
    run({1, 1, 1, 1, 6}, false);
    run({1, 5, 11, 5}, true);
}

TEST(random) {
    Rng rng(1100);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> nums = rng.ints(rng(1, 14), 1, 12);
        run(nums, brute(nums));
    }
}

TEST(large) {
    run(vector<int>(200, 1), true);
    vector<int> v(199, 100);
    v.push_back(2);
    run(v, false);
    v.assign(101, 100);
    v.insert(v.end(), 98, 1);
    run(v, false);
    v.assign(100, 100);
    v.insert(v.end(), 100, 1);
    run(v, true);
    Rng rng(1101);
    for (int iter = 0; iter < 4; ++iter) {
        vector<int> nums = rng.ints(200, 1, 100);
        if (accumulate(nums.begin(), nums.end(), 0) % 2) {
            nums[0] += nums[0] < 100 ? 1 : -1;
        }
        run(nums, bitset_oracle(nums));
    }
    vector<int> nums;
    for (int i = 0; i < 198; ++i) {
        nums.push_back(6 * rng(1, 16));
    }
    if (accumulate(nums.begin(), nums.end(), 0) / 6 % 2 == 0) {
        nums[0] += nums[0] <= 90 ? 6 : -6;
    }
    nums.insert(nums.end(), {1, 1});
    run(nums, bitset_oracle(nums));
}

}
