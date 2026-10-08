#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int target, int want) {
    vector<int> arg = nums;
    check(Solution().search(arg, target), want, "nums", nums, "target", target);
}

static int oracle(const vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == target) return static_cast<int>(i);
    }
    return -1;
}

static vector<int> distinct_sorted(Rng& rng, int n, int lo, int hi) {
    vector<int> all(hi - lo + 1);
    iota(all.begin(), all.end(), lo);
    rng.shuffle(all);
    all.resize(n);
    return sorted(all);
}

TEST(examples) {
    run({-8, -3, 0, 4, 9, 15}, 4, 3);
    run({-8, -3, 0, 4, 9, 15}, 5, -1);
    run({7}, 7, 0);
}

TEST(edge_cases) {
    run({7}, 6, -1);
    run({7}, 8, -1);
    run({1, 2}, 1, 0);
    run({1, 2}, 2, 1);
    run({1, 2}, 0, -1);
    run({1, 2}, 3, -1);
    run({1, 3}, 2, -1);
    run({-9999, 9999}, -9999, 0);
    run({-9999, 9999}, 9999, 1);
    run({-9999, 0, 9999}, 0, 1);
    run({-5, -4, -3, -2, -1}, -1, 4);
}

TEST(every_position) {
    Rng rng(28);
    for (int n = 1; n <= 40; ++n) {
        for (int rep = 0; rep < 3; ++rep) {
            vector<int> nums = distinct_sorted(rng, n, -60, 60);
            for (int target = nums[0] - 2; target <= nums.back() + 2; ++target) {
                run(nums, target, oracle(nums, target));
            }
        }
    }
    for (int n : {10000, 9999, 4096}) {
        vector<int> nums = distinct_sorted(rng, n, -9999, 9999), arg = nums;
        vector<int> index_of(19999, -1);
        for (int i = 0; i < n; ++i) {
            index_of[nums[i] + 9999] = i;
        }
        for (int target = -9999; target <= 9999; ++target) {
            check(Solution().search(arg, target), index_of[target + 9999], "nums", nums, "target", target);
        }
        ensure(arg == nums, "search() must not modify nums");
    }
}

TEST(many_searches) {
    const int n = 10000;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = 2 * i - 9999;
    }
    vector<int> arg = nums;
    Rng rng(704);
    for (int q = 0; q < 1000000; ++q) {
        int target = rng(-9999, 9999);
        int want = (target + 9999) % 2 == 0 ? (target + 9999) / 2 : -1;
        int got = Solution().search(arg, target);
        if (got != want) {
            check(got, want, "nums", nums, "target", target);
        }
        if (arg.size() != nums.size()) {
            fail("search() must not modify nums");
        }
    }
    ensure(arg == nums, "search() must not modify nums");
}

}
