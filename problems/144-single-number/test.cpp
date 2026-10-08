#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int want) {
    vector<int> arg = nums;
    check(Solution().singleNumber(arg), want, "nums", nums);
}

static vector<int> distinct_values(Rng& rng, int k) {
    unordered_set<int> seen;
    vector<int> out;
    while (static_cast<int>(out.size()) < k) {
        int v = rng(-30000, 30000);
        if (seen.insert(v).second) {
            out.push_back(v);
        }
    }
    return out;
}

static vector<int> build(Rng& rng, const vector<int>& values) {
    vector<int> nums(values.begin(), values.end());
    nums.insert(nums.end(), values.begin() + 1, values.end());
    rng.shuffle(nums);
    return nums;
}

TEST(examples) {
    run({7, 3, 7}, 3);
    run({5, -2, 9, -2, 5}, 9);
    run({42}, 42);
}

TEST(edge_cases) {
    run({0}, 0);
    run({-30000}, -30000);
    run({1, 1, 0}, 0);
    run({0, 0, -1}, -1);
    run({8, 4, 4}, 8);
    run({4, 4, 8}, 8);
    run({-5, 5, -5}, 5);
    run({30000, -30000, 30000}, -30000);
    run({2, 1, 3, 1, 2}, 3);
    run({-1, -2, -2}, -1);
}

TEST(large) {
    Rng rng(136);
    vector<int> values = distinct_values(rng, 15000);
    vector<int> nums = build(rng, values);
    nums.erase(find(nums.begin(), nums.end(), values[0]));
    nums.push_back(values[0]);
    run(nums, values[0]);
}

TEST(random) {
    Rng rng(1360);
    for (int k = 0; k < 500; ++k) {
        vector<int> values = distinct_values(rng, rng(1, 30));
        run(build(rng, values), values[0]);
    }
}

}
