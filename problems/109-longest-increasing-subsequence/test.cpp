#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().lengthOfLIS(arg), want, "nums", nums);
}

static int brute(const vector<int>& nums) {
    int n = nums.size(), best = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        int last = INT_MIN, len = 0;
        bool ok = true;
        for (int i = 0; i < n && ok; ++i) {
            if (mask >> i & 1) {
                if (len > 0 && nums[i] <= last) {
                    ok = false;
                }
                last = nums[i];
                ++len;
            }
        }
        if (ok) {
            best = max(best, len);
        }
    }
    return best;
}

static int lis_fenwick(const vector<int>& nums) {
    const int OFF = 10001, SIZE = 20002;
    vector<int> tree(SIZE + 1, 0);
    int best = 0;
    for (int x : nums) {
        int cur = 0;
        for (int i = x + OFF - 1; i > 0; i -= i & -i) {
            cur = max(cur, tree[i]);
        }
        ++cur;
        best = max(best, cur);
        for (int i = x + OFF; i <= SIZE; i += i & -i) {
            tree[i] = max(tree[i], cur);
        }
    }
    return best;
}

TEST(examples) {
    run({3, 1, 8, 2, 5}, 3);
    run({0, 8, 4, 12, 2, 10, 6, 14}, 4);
    run({5, 5, 5}, 1);
}

TEST(edge_cases) {
    run({7}, 1);
    run({1, 2}, 2);
    run({2, 1}, 1);
    run({-10000, 10000}, 2);
    run({1, 1, 2, 2, 3, 3}, 3);
    run({4, 10, 4, 3, 8, 9}, 3);
    run({1, 3, 6, 7, 9, 4, 10, 5, 6}, 6);
    run({9, 8, 1, 2, 7, 3, 4}, 4);
}

TEST(random) {
    Rng rng(1090);
    for (int iter = 0; iter < 300; ++iter) {
        vector<int> nums = rng.ints(rng(1, 12), -5, 5);
        run(nums, brute(nums));
    }
}

TEST(large) {
    const int n = 2500;
    vector<int> up(n), down(n);
    for (int i = 0; i < n; ++i) {
        up[i] = -n + 2 * i, down[i] = n - i;
    }
    run(up, n);
    run(down, 1);
    run(vector<int>(n, 7), 1);
    vector<int> blocks;
    for (int b = 0; b < 50; ++b) {
        for (int i = 0; i < 50; ++i) {
            blocks.push_back(b * 100 + 49 - i);
        }
    }
    run(blocks, 50);
    Rng rng(1091);
    for (int iter = 0; iter < 2; ++iter) {
        vector<int> nums = rng.ints(n, -10000, 10000);
        run(nums, lis_fenwick(nums));
    }
}

}
