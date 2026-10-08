#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int target, const vector<int>& nums, int want) {
    vector<int> arg = nums;
    check(Solution().minSubArrayLen(target, arg), want, "target", target, "nums", nums);
}

static int brute(int target, const vector<int>& nums) {
    int n = nums.size(), best = 0;
    for (int i = 0; i < n; ++i) {
        int64_t sum = 0;
        for (int j = i; j < n; ++j) {
            sum += nums[j];
            if (sum >= target && (best == 0 || j - i + 1 < best)) {
                best = j - i + 1;
            }
        }
    }
    return best;
}

static int by_binary_search(int target, const vector<int>& nums) {
    int n = nums.size(), best = 0;
    vector<int64_t> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(prefix.begin(), prefix.end(), prefix[i] + target);
        if (it == prefix.end()) break;
        int len = int(it - prefix.begin()) - i;
        if (best == 0 || len < best) {
            best = len;
        }
    }
    return best;
}

TEST(examples) {
    run(11, {2, 7, 1, 8, 2, 8}, 3);
    run(6, {1, 2, 6, 1}, 1);
    run(50, {5, 10, 15}, 0);
}

TEST(edge_cases) {
    run(1, {1}, 1);
    run(2, {1}, 0);
    run(10, {10}, 1);
    run(6, {1, 1, 1, 1, 1, 1}, 6);
    run(7, {1, 1, 1, 1, 1, 1}, 0);
    run(5, {2, 5, 5}, 1);
    run(8, {3, 3, 3, 1, 1, 5, 3}, 2);
    run(15, {1, 2, 3, 4, 5}, 5);
    run(12, {5, 1, 3, 5, 10, 7, 4, 9, 2, 8}, 2);
    run(100, {1, 1, 1, 1, 1, 100}, 1);
    run(10001, {10000, 1, 10000}, 2);
    run(1000000000, {10000, 10000}, 0);
}

TEST(random) {
    Rng rng(209);
    for (int it = 0; it < 1000; ++it) {
        vector<int> nums = rng.ints(rng(1, 12), 1, 10);
        int target = rng(1, 40);
        run(target, nums, brute(target, nums));
    }
}

const int n = 100000;

TEST(large) {
    vector<int> ones(n, 1);
    run(n, ones, n);
    run(1000000000, ones, 0);
    run(1000000000, vector<int>(n, 10000), n);
    vector<int> spike = ones;
    spike[n / 2] = 10000;
    run(10002, spike, 3);
}

TEST(large_random) {
    Rng rng(20900);
    for (int target : {1000000000, 300000000, 50000000, 1000000, 20000}) {
        vector<int> nums = rng.ints(n, 1, 10000);
        run(target, nums, by_binary_search(target, nums));
    }
}

}
