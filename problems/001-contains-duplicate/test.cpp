#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, bool want) {
    vector<int> arg = nums;
    check(Solution().containsDuplicate(arg), want, "nums", nums);
}

TEST(examples) {
    run({4, 8, 15, 4}, true);
    run({7, -2, 0, 11}, false);
    run({5, 5, 5, 5}, true);
}

TEST(edge_cases) {
    run({1}, false);
    run({0, 0}, true);
    run({-1, 1}, false);
    run({1000000000, -1000000000, 1000000000}, true);
    run({3, 1, 2, 5, 4, 3}, true);
}

TEST(large) {
    Rng rng(1);
    vector<int> nums(100000);
    iota(nums.begin(), nums.end(), -50000);
    rng.shuffle(nums);
    run(nums, false);
    nums.back() = nums.front();
    run(nums, true);
}

}
