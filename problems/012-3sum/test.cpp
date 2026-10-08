#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, vector<vector<int>> want) {
    vector<int> arg = nums;
    vector<vector<int>> got = Solution().threeSum(arg);
    for (const auto& t : got) {
        ensure(t.size() == 3, "every triplet must have exactly 3 values", "nums", nums, "got", got);
    }
    vector<vector<int>> canon = sort_all(got);
    ensure(adjacent_find(canon.begin(), canon.end()) == canon.end(),
           "the same triplet appears more than once", "nums", nums, "got", got);
    check(canon, sort_all(want), "nums", nums);
}

static vector<vector<int>> brute(const vector<int>& nums) {
    set<vector<int>> found;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    found.insert(sorted(vector<int>{nums[i], nums[j], nums[k]}));
                }
            }
        }
    }
    return {found.begin(), found.end()};
}

TEST(examples) {
    run({-2, 0, 1, 1, 2}, {{-2, 0, 2}, {-2, 1, 1}});
    run({1, 2, -4, 5}, {});
    run({0, 0, 0, 0}, {{0, 0, 0}});
}

TEST(edge_cases) {
    run({0, 0, 0}, {{0, 0, 0}});
    run({1, 1, 1}, {});
    run({-1, 0, 1, 0}, {{-1, 0, 1}});
    run({-2, 1, 1, 1}, {{-2, 1, 1}});
    run({-4, 2, 2, 2, 2}, {{-4, 2, 2}});
    run({100000, -100000, 0}, {{-100000, 0, 100000}});
    run({3, -2, 1, 0, -1, -3, 2}, {{-3, 0, 3}, {-3, 1, 2}, {-2, -1, 3}, {-2, 0, 2}, {-1, 0, 1}});
    run({-1, -1, -1, 2, 2, 2}, {{-1, -1, 2}});
    run({5, -5, 5, -5, 0, 0}, {{-5, 0, 5}});
}

TEST(random) {
    Rng rng(12);
    for (int i = 0; i < 300; ++i) {
        vector<int> nums = rng.ints(rng(3, 12), -6, 6);
        run(nums, brute(nums));
    }
}

TEST(large) {
    Rng rng(1212);
    vector<int> nums, specials;
    for (int i = 0; i < 2940; ++i) {
        nums.push_back(4 * rng(-25000, 24999) + 1);
    }
    for (int i = 0; i < 60; ++i) {
        specials.push_back(4 * rng(-100, 100));
    }
    nums.insert(nums.end(), specials.begin(), specials.end());
    rng.shuffle(nums);
    run(nums, brute(specials));
    run(vector<int>(3000, 0), {{0, 0, 0}});
}

}
