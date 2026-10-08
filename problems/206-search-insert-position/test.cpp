#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int target, int want) {
    vector<int> arg = nums;
    check(Solution().searchInsert(arg, target), want, "nums", nums, "target", target);
}

static int oracle(const vector<int>& nums, int target) {
    return count_if(nums.begin(), nums.end(), [&](int x) { return x < target; });
}

static vector<int> distinct_sorted(Rng& rng, int n, int lo, int hi) {
    vector<int> all(hi - lo + 1);
    iota(all.begin(), all.end(), lo);
    rng.shuffle(all);
    all.resize(n);
    return sorted(all);
}

TEST(examples) {
    run({-6, -1, 3, 8, 12}, 8, 3);
    run({-6, -1, 3, 8, 12}, 4, 3);
    run({-6, -1, 3, 8, 12}, 20, 5);
}

TEST(edge_cases) {
    run({5}, 5, 0);
    run({5}, 4, 0);
    run({5}, 6, 1);
    run({1, 3}, 0, 0);
    run({1, 3}, 1, 0);
    run({1, 3}, 2, 1);
    run({1, 3}, 3, 1);
    run({1, 3}, 4, 2);
    run({-6, -1, 3, 8, 12}, -6, 0);
    run({-6, -1, 3, 8, 12}, -7, 0);
    run({-6, -1, 3, 8, 12}, 12, 4);
    run({-6, -1, 3, 8, 12}, 11, 4);
    run({-10000, 10000}, -10000, 0);
    run({-10000, 10000}, 10000, 1);
    run({-10000, 10000}, 0, 1);
    run({-9999, 9999}, 10000, 2);
    run({-9999, 9999}, -10000, 0);
}

TEST(every_position) {
    Rng rng(35);
    for (int n = 1; n <= 40; ++n) {
        for (int rep = 0; rep < 3; ++rep) {
            vector<int> nums = distinct_sorted(rng, n, -60, 60);
            for (int target = nums[0] - 2; target <= nums.back() + 2; ++target) {
                run(nums, target, oracle(nums, target));
            }
        }
    }
    for (int n : {10000, 9999, 4096}) {
        vector<int> nums = distinct_sorted(rng, n, -10000, 10000), arg = nums;
        vector<int> below(20002, 0);
        for (int t = -10000, i = 0; t <= 10001; ++t) {
            while (i < n && nums[i] < t) {
                ++i;
            }
            below[t + 10000] = i;
        }
        for (int target = -10000; target <= 10000; ++target) {
            int got = Solution().searchInsert(arg, target);
            if (got != below[target + 10000]) {
                check(got, below[target + 10000], "nums", nums, "target", target);
            }
        }
        ensure(arg == nums, "searchInsert() must not modify nums");
    }
}

TEST(many_searches) {
    const int n = 10000;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = 2 * i - 9999;
    }
    vector<int> arg = nums;
    Rng rng(350);
    for (int q = 0; q < 1000000; ++q) {
        int target = rng(-10000, 10000);
        int want = (target + 10000) / 2;
        int got = Solution().searchInsert(arg, target);
        if (got != want) {
            check(got, want, "nums", nums, "target", target);
        }
        if (arg.size() != nums.size()) {
            fail("searchInsert() must not modify nums");
        }
    }
    ensure(arg == nums, "searchInsert() must not modify nums");
}

}
