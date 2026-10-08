#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, vector<vector<int>> want) {
    vector<int> arg = nums;
    auto got = sorted(Solution().permute(arg));
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the permutation " + repr(*d) + " appears more than once", "nums", nums, "got", got);
    }
    check(got, sorted(want), "nums", nums);
}

static vector<vector<int>> oracle(vector<int> nums) {
    vector<vector<int>> out;
    sort(nums.begin(), nums.end());
    do {
        out.push_back(nums);
    } while (next_permutation(nums.begin(), nums.end()));
    return out;
}

TEST(examples) {
    run({5, 8}, {{5, 8}, {8, 5}});
    run({0, -2, 3}, {{0, -2, 3}, {0, 3, -2}, {-2, 0, 3}, {-2, 3, 0}, {3, 0, -2}, {3, -2, 0}});
    run({4}, {{4}});
}

TEST(edge_cases) {
    run({0}, {{0}});
    run({-10, 10}, {{-10, 10}, {10, -10}});
    run({3, 2, 1}, {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}});
    vector<int> nums = {6, -1, 0, 10, -10, 4};
    run(nums, oracle(nums));
}

TEST(random) {
    Rng rng(46);
    for (int iter = 0; iter < 150; ++iter) {
        vector<int> pool(21);
        iota(pool.begin(), pool.end(), -10);
        rng.shuffle(pool);
        pool.resize(rng(1, 6));
        run(pool, oracle(pool));
    }
}

}
