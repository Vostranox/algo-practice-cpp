#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, vector<vector<int>> want) {
    vector<int> arg = nums;
    auto got = sort_all(Solution().subsetsWithDup(arg));
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the subset " + repr(*d) + " appears more than once", "nums", nums, "got", got);
    }
    check(got, sort_all(want), "nums", nums);
}

static vector<vector<int>> oracle(const vector<int>& nums) {
    set<vector<int>> found;
    for (int mask = 0; mask < (1 << nums.size()); ++mask) {
        vector<int> s;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (mask >> i & 1) {
                s.push_back(nums[i]);
            }
        }
        found.insert(sorted(s));
    }
    return vector<vector<int>>(found.begin(), found.end());
}

TEST(examples) {
    run({2, 5, 2}, {{}, {2}, {5}, {2, 2}, {2, 5}, {2, 2, 5}});
    run({7}, {{}, {7}});
    run({1, 1, 1}, {{}, {1}, {1, 1}, {1, 1, 1}});
}

TEST(edge_cases) {
    run({3, 3}, {{}, {3}, {3, 3}});
    run({0, -1}, {{}, {0}, {-1}, {-1, 0}});
    run({4, 4, 4, 1, 4}, {{}, {1}, {4}, {1, 4}, {4, 4}, {1, 4, 4}, {4, 4, 4}, {1, 4, 4, 4},
                          {4, 4, 4, 4}, {1, 4, 4, 4, 4}});
    vector<vector<int>> tens;
    for (int r = 0; r <= 10; ++r) {
        tens.push_back(vector<int>(r, -10));
    }
    run(vector<int>(10, -10), tens);
    vector<int> nums = {5, -5, 5, 0, -5, 5, 10, 0, -10, 5};
    run(nums, oracle(nums));
    nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    run(nums, oracle(nums));
}

TEST(random) {
    Rng rng(90);
    for (int iter = 0; iter < 150; ++iter) {
        vector<int> nums = rng.ints(rng(1, 10), -3, 3);
        run(nums, oracle(nums));
    }
}

}
