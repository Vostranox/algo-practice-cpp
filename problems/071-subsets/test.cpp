#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, vector<vector<int>> want) {
    vector<int> arg = nums;
    auto got = sort_all(Solution().subsets(arg));
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the subset " + repr(*d) + " appears more than once", "nums", nums, "got", got);
    }
    check(got, sort_all(want), "nums", nums);
}

static vector<vector<int>> oracle(const vector<int>& nums) {
    vector<vector<int>> out;
    for (int mask = 0; mask < (1 << nums.size()); ++mask) {
        out.emplace_back();
        for (size_t i = 0; i < nums.size(); ++i) {
            if (mask >> i & 1) {
                out.back().push_back(nums[i]);
            }
        }
    }
    return out;
}

TEST(examples) {
    run({4, 7}, {{}, {4}, {7}, {4, 7}});
    run({-1, 0, 5}, {{}, {-1}, {0}, {5}, {-1, 0}, {-1, 5}, {0, 5}, {-1, 0, 5}});
    run({9}, {{}, {9}});
}

TEST(edge_cases) {
    run({0}, {{}, {0}});
    run({-10, 10}, {{}, {-10}, {10}, {-10, 10}});
    run({3, 2, 1}, {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}});
    vector<int> nums = {7, -3, 0, 10, -10, 5, 2, -8, 9, 1};
    run(nums, oracle(nums));
}

TEST(random) {
    Rng rng(78);
    for (int iter = 0; iter < 120; ++iter) {
        vector<int> pool(21);
        iota(pool.begin(), pool.end(), -10);
        rng.shuffle(pool);
        pool.resize(rng(1, 10));
        run(pool, oracle(pool));
    }
}

}
