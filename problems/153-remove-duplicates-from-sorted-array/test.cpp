#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, const vector<int>& want) {
    vector<int> arg = nums;
    int k = Solution().removeDuplicates(arg);
    check(k, static_cast<int>(want.size()), "nums", nums);
    ensure(arg.size() >= static_cast<size_t>(k), "nums is shorter than the returned k", "nums", nums, "k", k,
           "nums after the call", arg);
    vector<int> front(arg.begin(), arg.begin() + k);
    ensure(front == want, "the first k positions don't hold the distinct values in order", "nums", nums, "k", k,
           "nums after the call", arg, "expected first k", want);
}

static vector<int> distinct(const vector<int>& nums) {
    set<int> s(nums.begin(), nums.end());
    return {s.begin(), s.end()};
}

TEST(examples) {
    run({3, 3, 7}, {3, 7});
    run({-2, -2, 0, 0, 0, 4, 9, 9}, {-2, 0, 4, 9});
    run({5}, {5});
}

TEST(edge_cases) {
    run({1, 2, 3}, {1, 2, 3});
    run({4, 4, 4, 4}, {4});
    run({7, 7, 8}, {7, 8});
    run({7, 8, 8}, {7, 8});
    run({-100, 100}, {-100, 100});
    run({-100, -100, 100, 100}, {-100, 100});
    run({0, 1, 1, 2, 2, 2, 3}, {0, 1, 2, 3});
    run({-1, 0, 0, 1, 1, 1, 1, 2}, {-1, 0, 1, 2});
    run({0, 0}, {0});
}

TEST(random) {
    Rng rng(26);
    for (int it = 0; it < 500; ++it) {
        vector<int> nums = sorted(rng.ints(rng(1, 15), -5, 5));
        run(nums, distinct(nums));
    }
}

TEST(large) {
    Rng rng(2626);
    const int n = 30000;
    run(vector<int>(n, -100), {-100});
    run(vector<int>(n, 100), {100});
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = -100 + i * 201 / n;
    }
    vector<int> all(201);
    iota(all.begin(), all.end(), -100);
    run(nums, all);
    for (int it = 0; it < 14; ++it) {
        nums.clear();
        for (int v = -100; v <= 100 && static_cast<int>(nums.size()) < n; ++v) {
            if (rng.coin(0.8)) {
                nums.insert(nums.end(), rng(1, 290), v);
            }
        }
        nums.resize(n, 100);
        run(nums, distinct(nums));
    }
}

}
