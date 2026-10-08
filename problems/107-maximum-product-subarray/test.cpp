#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().maxProduct(arg), want, "nums", nums);
}

static int64_t brute(const vector<int>& nums) {
    int64_t best = INT64_MIN;
    for (size_t i = 0; i < nums.size(); ++i) {
        int64_t p = 1;
        for (size_t j = i; j < nums.size(); ++j) {
            best = max(best, p *= nums[j]);
        }
    }
    return best;
}

static int64_t product(const vector<int>& v, size_t lo, size_t hi) {
    int64_t p = 1;
    for (size_t i = lo; i < hi; ++i) {
        p *= v[i];
    }
    return p;
}

static int64_t by_segments(const vector<int>& nums) {
    int64_t best = *max_element(nums.begin(), nums.end());
    vector<vector<int>> blocks(1);
    for (int x : nums) {
        if (x == 0) {
            blocks.emplace_back();
        } else {
            blocks.back().push_back(x);
        }
    }
    for (auto& b : blocks) {
        if (b.empty()) continue;
        vector<size_t> negs;
        for (size_t i = 0; i < b.size(); ++i) {
            if (b[i] < 0) {
                negs.push_back(i);
            }
        }
        if (negs.size() % 2 == 0) {
            best = max(best, product(b, 0, b.size()));
        } else {
            if (negs.front() + 1 < b.size()) {
                best = max(best, product(b, negs.front() + 1, b.size()));
            }
            if (negs.back() > 0) {
                best = max(best, product(b, 0, negs.back()));
            }
        }
    }
    return best;
}

TEST(examples) {
    run({3, -1, 4, 2}, 8);
    run({-2, 3, -4}, 24);
    run({-2, 0, -1}, 0);
}

TEST(edge_cases) {
    run({-5}, -5);
    run({0}, 0);
    run({7}, 7);
    run({-2, -3}, 6);
    run({-1, -1, -1}, 1);
    run({0, -3, 0}, 0);
    run({-3, 0, -2}, 0);
    run({2, -5, -2, -4, 3}, 24);
    run(vector<int>(9, 10), 1000000000);
    run(vector<int>(9, -10), 100000000);
    run({-2, 1, 1, 1}, 1);
}

TEST(random) {
    Rng rng(1070);
    for (int iter = 0; iter < 400; ++iter) {
        vector<int> nums = rng.ints(rng(1, 10), -4, 4);
        run(nums, static_cast<int>(brute(nums)));
    }
}

TEST(large) {
    run(vector<int>(20000, 1), 1);
    run(vector<int>(20000, -1), 1);
    vector<int> v(19999, -1);
    v.push_back(-2);
    run(v, 2);
    Rng rng(1071);
    for (double zeroRate : {0.002, 0.0002, 0.0}) {
        vector<int> nums(20000);
        for (int& x : nums) {
            x = rng.coin(zeroRate) ? 0 : rng.pick(vector<int>{-1, 1, 1});
        }
        for (int k = 0; k < 30; ++k) {
            nums[rng(0, 19999)] = rng.coin() ? 2 : -2;
        }
        run(nums, static_cast<int>(by_segments(nums)));
    }
}

}
