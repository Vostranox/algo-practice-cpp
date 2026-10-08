#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int target, vector<int> want) {
    vector<int> arg = nums;
    vector<int> got = Solution().twoSum(arg, target);
    ensure(got.size() == 2, "should return exactly two indices", "nums", nums, "target", target, "got", got);
    check(sorted(got), sorted(want), "nums", nums, "target", target);
}

TEST(examples) {
    run({5, 2, 8}, 10, {1, 2});
    run({-3, 4, 3, 90}, 0, {0, 2});
    run({6, 6}, 12, {0, 1});
}

TEST(edge_cases) {
    run({4, 1, 7, 2}, 8, {1, 2});
    run({0, 4, 3, 0}, 0, {0, 3});
    run({-1, -2, -3, -4, -5}, -8, {2, 4});
    run({1000000000, -1000000000, 3}, 0, {0, 1});
    run({1, 5, 1}, 2, {0, 2});
    run({1, 2, 4, 8, 16}, 17, {0, 4});
    run({7, 1000000000, -999999999, 2}, 1, {1, 2});
}

TEST(random) {
    Rng rng(3);
    for (int done = 0; done < 300;) {
        vector<int> nums = rng.ints(rng(2, 9), -20, 20);
        int target = rng(-40, 40);
        vector<vector<int>> pairs;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            for (int j = i + 1; j < static_cast<int>(nums.size()); ++j) {
                if (nums[i] + nums[j] == target) {
                    pairs.push_back({i, j});
                }
            }
        }
        if (pairs.size() == 1) {
            run(nums, target, pairs[0]);
            ++done;
        }
    }
}

TEST(large) {
    Rng rng(33);
    const int n = 10000;
    for (int c = 0; c < 4; ++c) {
        unordered_set<int> seen;
        vector<int> nums;
        while (static_cast<int>(nums.size()) < n - 2) {
            int x = 4 * rng(-200000000, 200000000);
            if (seen.insert(x).second) {
                nums.push_back(x);
            }
        }
        int a = 4 * rng(-1000, 1000) + 1, b = 4 * rng(-1000, 1000) + 2;
        int i = c == 0 ? 0 : rng(0, n - 1), j = c == 0 ? n - 1 : rng(0, n - 1);
        if (i == j) {
            j = (i + 1) % n;
        }
        nums.insert(nums.begin() + min(i, j), 0);
        nums.insert(nums.begin() + max(i, j), 0);
        nums[i] = a;
        nums[j] = b;
        run(nums, a + b, {i, j});
    }
}

}
