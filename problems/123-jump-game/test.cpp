#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, bool want) {
    vector<int> arg = nums;
    check(Solution().canJump(arg), want, "nums", nums);
}

static bool brute(const vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    vector<bool> seen(n);
    seen[0] = true;
    for (int i = 0; i < n; ++i) {
        if (seen[i]) {
            for (int j = i + 1; j < n && j <= i + nums[i]; ++j) {
                seen[j] = true;
            }
        }
    }
    return seen[n - 1];
}

TEST(examples) {
    run({1, 3, 0, 0, 2}, true);
    run({2, 1, 0, 4}, false);
    run({0}, true);
}

TEST(edge_cases) {
    run({5}, true);
    run({0, 1}, false);
    run({1, 0}, true);
    run({1, 1, 1, 0}, true);
    run({1, 0, 1}, false);
    run({2, 0, 0, 1}, false);
    run({3, 0, 0, 0}, true);
    run({1, 2, 0, 0, 1}, false);
    run({2, 0, 2, 0, 0}, true);
    run({100000, 0, 0, 0}, true);
    run({4, 3, 2, 1, 0, 5}, false);
}

TEST(random) {
    Rng rng(55);
    vector<int> choices = {0, 0, 1, 1, 2, 3, 4};
    for (int it = 0; it < 600; ++it) {
        vector<int> nums(rng(1, 12));
        for (int& x : nums) {
            x = rng.pick(choices);
        }
        run(nums, brute(nums));
    }
}

TEST(large) {
    const int n = 10000;
    for (int k = 0; k < 3; ++k) {
        int m = n - k;
        vector<int> trap(m);
        for (int i = 0; i < m - 1; ++i) {
            trap[i] = m - 2 - i;
        }
        run(trap, false);
        vector<int> escape = trap;
        escape[0] = m - 1;
        run(escape, true);
        vector<int> bridge = trap;
        bridge[m - 2] = 1;
        run(bridge, true);
    }
    vector<int> ones(n, 1);
    ones.back() = 0;
    run(ones, true);
    vector<int> blocked(n, 7);
    fill(blocked.begin(), blocked.begin() + 5000, 1);
    blocked[5000] = 0;
    run(blocked, false);
    run(vector<int>(n, 100000), true);
    Rng rng(9);
    for (int it = 0; it < 5; ++it) {
        vector<int> nums = rng.ints(n, 0, 3);
        run(nums, brute(nums));
    }
}

}
