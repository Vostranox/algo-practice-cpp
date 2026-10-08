#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int val, vector<int> kept) {
    vector<int> arg = nums;
    int k = Solution().removeElement(arg, val);
    check(k, static_cast<int>(kept.size()), "nums", nums, "val", val);
    ensure(arg.size() >= static_cast<size_t>(k), "nums is shorter than the returned k", "nums", nums, "val", val, "k", k,
           "nums after the call", arg);
    vector<int> front(arg.begin(), arg.begin() + k);
    ensure(sorted(front) == sorted(kept), "the first k positions don't hold exactly the values different from val",
           "nums", nums, "val", val, "k", k, "nums after the call", arg, "expected (any order)", kept);
}

static vector<int> without(const vector<int>& nums, int val) {
    vector<int> out;
    for (int x : nums) {
        if (x != val) {
            out.push_back(x);
        }
    }
    return out;
}

TEST(examples) {
    run({4, 1, 4, 2}, 4, {1, 2});
    run({0, 5, 5, 3, 5, 0, 7}, 5, {0, 3, 0, 7});
    run({6, 6}, 6, {});
}

TEST(edge_cases) {
    run({}, 0, {});
    run({7}, 7, {});
    run({7}, 3, {7});
    run({1, 2, 3}, 100, {1, 2, 3});
    run({1, 2, 3}, 4, {1, 2, 3});
    run({0, 0, 1}, 0, {1});
    run({2, 9, 9, 9}, 2, {9, 9, 9});
    run({9, 9, 9, 2}, 2, {9, 9, 9});
    run({3, 3, 1, 3, 3, 1, 3}, 3, {1, 1});
    run({50, 0, 50, 0}, 50, {0, 0});
}

TEST(random) {
    Rng rng(152);
    for (int i = 0; i < 500; ++i) {
        vector<int> nums = rng.ints(rng(0, 12), 0, 4);
        int val = rng(0, 5);
        run(nums, val, without(nums, val));
    }
}

TEST(large) {
    Rng rng(1520);
    for (int i = 0; i < 50; ++i) {
        vector<int> nums = rng.ints(100, 0, rng(0, 50));
        int val = rng.coin(0.8) ? rng.pick(nums) : rng(0, 100);
        run(nums, val, without(nums, val));
    }
    run(vector<int>(100, 50), 50, {});
    run(vector<int>(100, 50), 49, vector<int>(100, 50));
}

}
