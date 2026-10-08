#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int want) {
    vector<int> arg = nums;
    check(Solution().singleNumber(arg), want, "nums", nums);
}

static vector<int> distinct_values(Rng& rng, int k, int64_t lo = INT_MIN, int64_t hi = INT_MAX) {
    unordered_set<int> seen;
    vector<int> out;
    while (static_cast<int>(out.size()) < k) {
        int v = static_cast<int>(rng.range(lo, hi));
        if (seen.insert(v).second) {
            out.push_back(v);
        }
    }
    return out;
}

static vector<int> build(Rng& rng, const vector<int>& values) {
    vector<int> nums(values.begin(), values.end());
    for (int rep = 0; rep < 2; ++rep) {
        nums.insert(nums.end(), values.begin() + 1, values.end());
    }
    rng.shuffle(nums);
    return nums;
}

TEST(examples) {
    run({4, -1, 4, 4}, -1);
    run({6, 0, 6, -3, 0, 6, 0}, -3);
    run({INT_MIN, 7, 7, 7}, INT_MIN);
}

TEST(edge_cases) {
    run({0}, 0);
    run({-1}, -1);
    run({INT_MAX}, INT_MAX);
    run({INT_MIN}, INT_MIN);
    run({1, 1, 1, 0}, 0);
    run({0, 0, 0, 1}, 1);
    run({-1, -1, -1, 0}, 0);
    run({0, -1, -1, -1}, 0);
    run({5, 5, 5, -1}, -1);
    run({-5, 5, -5, -5}, 5);
    run({5, -5, 5, 5}, -5);
    run({INT_MIN, INT_MIN, INT_MAX, INT_MIN}, INT_MAX);
    run({INT_MAX, INT_MIN, INT_MAX, INT_MAX}, INT_MIN);
    run({INT_MIN, INT_MIN, INT_MIN, -1}, -1);
    run({-1, -1, INT_MIN, -1}, INT_MIN);
    run({2, 3, 2, 3, 9, 3, 2}, 9);
    run({-7, -8, -8, -9, -9, -8, -9}, -7);
    run({1 << 30, 3, 1 << 30, 3, 1 << 30, 3, -(1 << 30)}, -(1 << 30));
    run({INT_MAX, INT_MAX, INT_MAX, INT_MIN + 1, INT_MIN, INT_MIN, INT_MIN}, INT_MIN + 1);
}

TEST(large) {
    Rng rng(137);
    vector<int> values = distinct_values(rng, 10000, INT_MIN, 1000);
    run(build(rng, values), values[0]);
    vector<int> nums = build(rng, values);
    nums.erase(find(nums.begin(), nums.end(), values[0]));
    nums.push_back(values[0]);
    run(nums, values[0]);
}

TEST(random) {
    Rng rng(1370);
    for (int k = 0; k < 1000; ++k) {
        int count = rng(1, 30);
        vector<int> values = rng.coin() ? distinct_values(rng, count) : distinct_values(rng, count, -50, 50);
        run(build(rng, values), values[0]);
    }
}

}
