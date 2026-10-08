#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().rob(arg), want, "nums", nums);
}

static int brute(const vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    int best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            if (!(mask >> i & 1)) continue;
            if (mask >> ((i + 1) % n) & 1) {
                ok = false;
            }
            total += nums[i];
        }
        if (ok) {
            best = max(best, total);
        }
    }
    return best;
}

static int64_t circle_dp(const vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    const int64_t NEG = INT64_MIN / 4;
    int64_t best[2][2] = {{0, NEG}, {NEG, nums[0]}};
    for (int i = 1; i < n; ++i) {
        int64_t next[2][2];
        for (int first = 0; first < 2; ++first) {
            next[first][1] = best[first][0] + nums[i];
            next[first][0] = max(best[first][0], best[first][1]);
        }
        memcpy(best, next, sizeof best);
    }
    return max({best[0][0], best[0][1], best[1][0]});
}

TEST(examples) {
    run({3, 4, 3}, 4);
    run({2, 9, 4, 1, 8}, 17);
    run({6, 2, 1, 7}, 9);
}

TEST(edge_cases) {
    run({5}, 5);
    run({0}, 0);
    run({1, 5}, 5);
    run({5, 1}, 5);
    run({2, 3, 2}, 3);
    run({9, 1, 1, 9}, 10);
    run({1, 2, 3, 1}, 4);
    run({0, 0, 0, 0}, 0);
}

TEST(random) {
    Rng rng(1020);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> nums = rng.ints(rng(1, 14), 0, 30);
        run(nums, brute(nums));
    }
}

TEST(large) {
    run(vector<int>(100, 1000), 1000 * 50);
    run(vector<int>(99, 1000), 1000 * 49);
    Rng rng(1021);
    for (int iter = 0; iter < 5; ++iter) {
        vector<int> nums = rng.ints(100, 0, 1000);
        run(nums, static_cast<int>(circle_dp(nums)));
    }
}

}
