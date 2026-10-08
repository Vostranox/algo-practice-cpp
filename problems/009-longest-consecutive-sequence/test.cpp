#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().longestConsecutive(arg), want, "nums", nums);
}

static int brute(const vector<int>& nums) {
    set<int64_t> s(nums.begin(), nums.end());
    int best = 0;
    for (int64_t x : s) {
        int len = 1;
        while (s.count(x + len)) {
            ++len;
        }
        best = max(best, len);
    }
    return best;
}

TEST(examples) {
    run({7, 50, 5, 6, 100, 4, 8}, 5);
    run({0, -1, 1, 1, -2, 9}, 4);
    run({}, 0);
}

TEST(edge_cases) {
    run({5}, 1);
    run({2, 2, 2}, 1);
    run({1, 3, 5, 7}, 1);
    run({1, 2, 0, 1}, 3);
    run({1000000000, -1000000000}, 1);
    run({1000000000, 999999999}, 2);
    run({-999999998, -1000000000, -999999999}, 3);
    run({3, 2, 1, 10, 11, 12}, 3);
    run({9, 1, 4, 7, 3, -1, 0, 5, 8, -1, 6}, 7);
}

TEST(random) {
    Rng rng(9);
    for (int i = 0; i < 300; ++i) {
        vector<int> nums = rng.ints(rng(0, 20), -15, 15);
        run(nums, brute(nums));
    }
}

TEST(large) {
    Rng rng(99);
    const int n = 100000;
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), -1000000000);
    rng.shuffle(nums);
    run(nums, n);
    nums.clear();
    for (int i = 0; i < 30000; ++i) {
        nums.push_back(5000 + i);
    }
    for (int i = 0; i < 70000; ++i) {
        nums.push_back(100000000 + 2 * i);
    }
    rng.shuffle(nums);
    run(nums, 30000);
    nums.clear();
    for (int i = 0; i < 50000; ++i) {
        nums.push_back(i), nums.push_back(i);
    }
    rng.shuffle(nums);
    run(nums, 50000);
}

}
