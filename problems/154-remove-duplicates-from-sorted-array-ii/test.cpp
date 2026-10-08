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
    ensure(front == want, "the first k positions don't hold the kept values in order", "nums", nums, "k", k,
           "nums after the call", arg, "expected first k", want);
}

static vector<int> at_most_twice(const vector<int>& nums) {
    map<int, int> count;
    for (int x : nums) {
        ++count[x];
    }
    vector<int> out;
    for (auto [v, c] : count) {
        out.insert(out.end(), min(c, 2), v);
    }
    return out;
}

TEST(examples) {
    run({4, 4, 4, 6}, {4, 4, 6});
    run({-1, 0, 0, 0, 0, 2, 3, 3, 3}, {-1, 0, 0, 2, 3, 3});
    run({8, 9}, {8, 9});
}

TEST(edge_cases) {
    run({5}, {5});
    run({5, 5}, {5, 5});
    run({5, 5, 5}, {5, 5});
    run({5, 5, 5, 5, 5, 5, 5}, {5, 5});
    run({1, 2, 3}, {1, 2, 3});
    run({1, 1, 1, 2, 2, 2}, {1, 1, 2, 2});
    run({1, 2, 2, 2, 3}, {1, 2, 2, 3});
    run({0, 1, 1, 1, 1, 2, 2, 3}, {0, 1, 1, 2, 2, 3});
    run({1, 1, 1, 1, 2, 2, 2, 3, 3, 3}, {1, 1, 2, 2, 3, 3});
    run({1, 1, 2, 3, 3, 3, 4}, {1, 1, 2, 3, 3, 4});
    run({-10000, -10000, -10000, 10000, 10000, 10000}, {-10000, -10000, 10000, 10000});
}

TEST(random) {
    Rng rng(80);
    for (int it = 0; it < 500; ++it) {
        vector<int> nums = sorted(rng.ints(rng(1, 15), -4, 4));
        run(nums, at_most_twice(nums));
    }
}

TEST(large) {
    Rng rng(8080);
    const int n = 30000;
    run(vector<int>(n, 10000), {10000, 10000});
    run(vector<int>(n, -10000), {-10000, -10000});
    vector<int> pairs(n);
    for (int i = 0; i < n; ++i) {
        pairs[i] = -10000 + i / 2;
    }
    run(pairs, pairs);
    vector<int> runs;
    for (int v = -10000, len = 1; static_cast<int>(runs.size()) < n; ++v, len = len % 7 + 1) {
        runs.insert(runs.end(), len, v);
    }
    runs.resize(n);
    run(runs, at_most_twice(runs));
    for (int it = 0; it < 14; ++it) {
        vector<int> nums;
        for (int v = rng(-10000, -9000); static_cast<int>(nums.size()) < n; v += rng(1, 3)) {
            nums.insert(nums.end(), rng(1, 300), v);
        }
        nums.resize(n);
        run(nums, at_most_twice(nums));
    }
    vector<int> narrow = sorted(rng.ints(n, -100, 100));
    run(narrow, at_most_twice(narrow));
}

}
