#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().maxSubarraySumCircular(arg), want, "nums", nums);
}

static int brute(const vector<int>& nums) {
    int n = nums.size();
    int64_t best = INT64_MIN;
    for (int s = 0; s < n; ++s) {
        int64_t sum = 0;
        for (int len = 1; len <= n; ++len) {
            best = max(best, sum += nums[(s + len - 1) % n]);
        }
    }
    return static_cast<int>(best);
}

static int windowed(const vector<int>& nums) {
    int n = nums.size();
    vector<int64_t> P(2 * n + 1, 0);
    for (int j = 1; j <= 2 * n; ++j) {
        P[j] = P[j - 1] + nums[(j - 1) % n];
    }
    deque<int> lows;
    int64_t best = INT64_MIN;
    for (int j = 1; j <= 2 * n; ++j) {
        while (!lows.empty() && P[lows.back()] >= P[j - 1]) {
            lows.pop_back();
        }
        lows.push_back(j - 1);
        if (lows.front() < j - n) {
            lows.pop_front();
        }
        best = max(best, P[j] - P[lows.front()]);
    }
    return static_cast<int>(best);
}

TEST(examples) {
    run({6, -9, 1, 7}, 14);
    run({-2, 4, 5, -3}, 9);
    run({-4, -2, -7}, -2);
}

TEST(edge_cases) {
    run({5}, 5);
    run({-5}, -5);
    run({0}, 0);
    run({-3, 0}, 0);
    run({0, -1, 0}, 0);
    run({5, -3, 5}, 10);
    run({-1, 3, -1}, 3);
    run({3, -1, 2}, 5);
    run({1, 2, 3}, 6);
    run({2, -1, -1, 2}, 4);
    run({-5, 3, 3, -5}, 6);
    run({-2, -3, -1}, -1);
    run({-30000, -30000}, -30000);
    run({30000, 30000, -30000, 30000}, 90000);
}

TEST(random) {
    Rng rng(205);
    for (int iter = 0; iter < 600; ++iter) {
        int n = rng(1, 12);
        vector<int> nums = rng.coin(0.15) ? rng.ints(n, -10, -1) : rng.ints(n, -10, 10);
        run(nums, brute(nums));
    }
}

TEST(large) {
    const int n = 30000;
    Rng rng(918);
    vector<int> nums = rng.ints(n, -30000, -1);
    run(nums, *max_element(nums.begin(), nums.end()));
    run(vector<int>(n, 30000), 900000000);
    run(vector<int>(n, -30000), -30000);
    nums.assign(n, -30000);
    fill(nums.begin(), nums.begin() + 1000, 30000);
    fill(nums.end() - 1000, nums.end(), 30000);
    run(nums, 60000000);
    for (int iter = 0; iter < 4; ++iter) {
        nums = rng.ints(n, -30000, 30000);
        if (iter % 2) {
            int shift = iter == 1 ? 3000 : -3000;
            for (int& x : nums) {
                x = max(-30000, min(30000, x + shift));
            }
        }
        run(nums, windowed(nums));
    }
}

}
