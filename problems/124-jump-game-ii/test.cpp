#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().jump(arg), want, "nums", nums);
}

static int min_jumps(const vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    vector<int> dist(n, -1);
    dist[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[i] < 0) continue;
        for (int j = i + 1; j < n && j <= i + nums[i]; ++j) {
            if (dist[j] < 0 || dist[i] + 1 < dist[j]) {
                dist[j] = dist[i] + 1;
            }
        }
    }
    return dist[n - 1];
}

TEST(examples) {
    run({4, 1, 1, 3, 1, 1, 1}, 2);
    run({1, 1, 1, 1}, 3);
    run({0}, 0);
}

TEST(edge_cases) {
    run({7}, 0);
    run({1, 0}, 1);
    run({5, 0, 0}, 1);
    run({2, 0, 2, 0, 1}, 2);
    run({1, 4, 0, 0, 0, 1}, 2);
    run({3, 1, 1, 1, 1}, 2);
    run({1, 1, 3, 0, 0, 0}, 3);
    run({2, 3, 0, 1, 4, 0, 0, 1}, 3);
    vector<int> one_jump(1001, 0);
    one_jump[0] = 1000;
    run(one_jump, 1);
}

TEST(random) {
    Rng rng(45);
    vector<int> choices = {0, 1, 1, 2, 2, 3, 4, 5};
    for (int done = 0; done < 600;) {
        vector<int> nums(rng(1, 12));
        for (int& x : nums) {
            x = rng.pick(choices);
        }
        int want = min_jumps(nums);
        if (want < 0) continue;
        run(nums, want);
        ++done;
    }
}

TEST(large) {
    const int n = 10000;
    for (int m : {n, n - 1}) {
        run(vector<int>(m, 1), m - 1);
        run(vector<int>(m, 2), m / 2);
    }
    run(vector<int>(n, 1000), 10);
    vector<int> saw(n), spikes(n);
    for (int i = 0; i < n; ++i) {
        saw[i] = 1000 - i % 1000;
        spikes[i] = i % 1000 == 0 ? 1000 : 1;
    }
    run(saw, 10);
    run(spikes, 10);
    Rng rng(4);
    for (int it = 0; it < 3; ++it) {
        vector<int> nums = rng.ints(n, 1, 8);
        run(nums, min_jumps(nums));
    }
}

}
