#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int target, int want) {
    vector<int> arg = nums;
    check(Solution().findTargetSumWays(arg, target), want, "nums", nums, "target", target);
}

static int brute(const vector<int>& nums, int target) {
    int n = nums.size(), count = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int value = 0;
        for (int i = 0; i < n; ++i) {
            value += mask >> i & 1 ? -nums[i] : nums[i];
        }
        count += value == target;
    }
    return count;
}

static int64_t subset_count(const vector<int>& nums, int target) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (abs(target) > total || (total + target) % 2) return 0;
    int want = (total + target) / 2;
    vector<int64_t> ways(want + 1, 0);
    ways[0] = 1;
    for (int x : nums) {
        for (int s = want; s >= x; --s) {
            ways[s] += ways[s - x];
        }
    }
    return ways[want];
}

static int64_t binom(int a, int b) {
    if (b < 0 || b > a) return 0;
    int64_t c = 1;
    for (int i = 1; i <= b; ++i) {
        c = c * (a - b + i) / i;
    }
    return c;
}

TEST(examples) {
    run({2, 1, 1}, 2, 2);
    run({1, 2, 3}, 0, 2);
    run({0, 0, 1}, 1, 4);
}

TEST(edge_cases) {
    run({1}, 2, 0);
    run({1}, -1, 1);
    run({1000}, -1000, 1);
    run({0}, 0, 2);
    run({7, 7}, 0, 2);
    run({3}, 1, 0);
    run({1, 1, 1, 1, 1}, 3, 5);
    run({1, 2, 3}, 7, 0);
    run({5, 5}, -10, 1);
}

TEST(random) {
    Rng rng(1150);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> nums = rng.ints(rng(1, 12), 0, 15);
        int total = accumulate(nums.begin(), nums.end(), 0);
        int target = rng(-total - 2, total + 2);
        run(nums, target, brute(nums, target));
    }
}

TEST(large) {
    run(vector<int>(20, 0), 0, 1 << 20);
    for (int t : {0, 2, -6, 20, -20, 1, 21}) {
        run(vector<int>(20, 1), t, static_cast<int>((20 + t) % 2 ? 0 : binom(20, (20 + t) / 2)));
    }
    vector<int> mixed(10, 0);
    mixed.insert(mixed.end(), 10, 1);
    run(mixed, 0, 1024 * 252);
    run(vector<int>(20, 50), 0, static_cast<int>(binom(20, 10)));
    run(vector<int>(20, 50), 1000, 1);
    Rng rng(1151);
    vector<int> nums20 = rng.ints(20, 0, 50);
    run(nums20, 10, brute(nums20, 10));
    for (int iter = 0; iter < 6; ++iter) {
        vector<int> nums = rng.ints(20, 0, 50);
        int total = accumulate(nums.begin(), nums.end(), 0);
        int target = rng(-total, total);
        run(nums, target, static_cast<int>(subset_count(nums, target)));
    }
}

}
