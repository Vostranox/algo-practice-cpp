#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int k, vector<int> want) {
    vector<int> arg = nums;
    check(Solution().maxSlidingWindow(arg, k), want, "nums", nums, "k", k);
}

static vector<int> brute(const vector<int>& nums, int k) {
    vector<int> res;
    for (size_t i = 0; i + k <= nums.size(); ++i) {
        res.push_back(*max_element(nums.begin() + i, nums.begin() + i + k));
    }
    return res;
}

static vector<int> oracle(const vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> pre = nums, suf = nums, res;
    for (int i = 1; i < n; ++i) {
        if (i % k) {
            pre[i] = max(pre[i - 1], nums[i]);
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        if ((i + 1) % k) {
            suf[i] = max(suf[i + 1], nums[i]);
        }
    }
    for (int i = 0; i + k <= n; ++i) {
        res.push_back(max(suf[i], pre[i + k - 1]));
    }
    return res;
}

TEST(examples) {
    run({4, 2, 12, 3, 8, 1, 7}, 3, {12, 12, 12, 8, 8});
    run({9, 8, 7, 6}, 2, {9, 8, 7});
    run({5}, 1, {5});
}

TEST(edge_cases) {
    run({1, -1}, 1, {1, -1});
    run({3, 1, 2}, 3, {3});
    run({2, 2, 2}, 2, {2, 2});
    run({-5, -3, -9, -1}, 2, {-3, -3, -1});
    run({1, 2, 3, 4, 5}, 2, {2, 3, 4, 5});
    run({3, 1, 3, 1, 1}, 2, {3, 3, 3, 1});
    run({1, 3, 1, 2, 0, 5}, 3, {3, 3, 2, 5});
    run({7, 2, 4}, 2, {7, 4});
    run({-10000, 10000, -10000}, 2, {10000, 10000});
}

TEST(random) {
    Rng rng(20);
    for (int i = 0; i < 300; ++i) {
        vector<int> nums = rng.ints(rng(1, 15), -10, 10);
        int k = rng(1, static_cast<int>(nums.size()));
        run(nums, k, brute(nums, k));
    }
}

TEST(large) {
    Rng rng(2020);
    const int n = 100000, k = 50000;
    vector<int> rising(n);
    for (int i = 0; i < n; ++i) {
        rising[i] = -10000 + i / 5;
    }
    run(rising, k, vector<int>(rising.begin() + k - 1, rising.end()));
    vector<int> falling(rising.rbegin(), rising.rend());
    run(falling, k, vector<int>(falling.begin(), falling.begin() + n - k + 1));
    vector<int> nums = rng.ints(n, -10000, 10000);
    run(nums, k, oracle(nums, k));
    run(nums, 1000, oracle(nums, 1000));
    run(nums, n, {*max_element(nums.begin(), nums.end())});
    run(nums, 1, nums);
}

}
