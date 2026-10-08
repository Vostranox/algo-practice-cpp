#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().maxCoins(arg), want, "nums", nums);
}

static int brute(const vector<int>& nums) {
    vector<int> order(nums.size());
    iota(order.begin(), order.end(), 0);
    int best = 0;
    do {
        vector<int> row = nums;
        vector<int> idx(nums.size());
        iota(idx.begin(), idx.end(), 0);
        int total = 0;
        for (int b : order) {
            int at = find(idx.begin(), idx.end(), b) - idx.begin();
            int left = at > 0 ? row[at - 1] : 1, right = at + 1 < static_cast<int>(row.size()) ? row[at + 1] : 1;
            total += left * row[at] * right;
            row.erase(row.begin() + at);
            idx.erase(idx.begin() + at);
        }
        best = max(best, total);
    } while (next_permutation(order.begin(), order.end()));
    return best;
}

static int interval_oracle(const vector<int>& nums) {
    int n = nums.size();
    auto at = [&](int i) { return i < 0 || i >= n ? 1 : nums[i]; };
    vector<vector<int>> best(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {
            int out = 0;
            for (int k = i; k <= j; ++k) {
                out = max(out, best[i][k] + at(i - 1) * nums[k] * at(j + 1) + best[k + 1][j + 1]);
            }
            best[i][j + 1] = out;
        }
    }
    return best[0][n];
}

TEST(examples) {
    run({2, 4, 3}, 33);
    run({1, 5}, 10);
    run({5}, 5);
}

TEST(edge_cases) {
    run({0}, 0);
    run({0, 0, 0}, 0);
    run({7, 0, 7}, 56);
    run({3, 1, 5, 8}, 167);
    run({100, 100, 100}, 1010100);
    run({1, 1}, 2);
}

TEST(random) {
    Rng rng(1200);
    for (int iter = 0; iter < 120; ++iter) {
        vector<int> nums = rng.ints(rng(1, 7), 0, 9);
        run(nums, brute(nums));
    }
}

TEST(large) {
    run(vector<int>(300, 100), 298 * 1000000 + 10000 + 100);
    run(vector<int>(300, 1), 300);
    Rng rng(1201);
    vector<int> nums = rng.ints(300, 0, 100);
    run(nums, interval_oracle(nums));
}

}
