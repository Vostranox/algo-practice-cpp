#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int k, vector<int> want) {
    vector<int> arg = nums;
    vector<int> got = Solution().topKFrequent(arg, k);
    check(sorted(got), sorted(want), "nums", nums, "k", k);
}

static optional<vector<int>> brute(const vector<int>& nums, int k) {
    map<int, int> count;
    for (int x : nums) {
        ++count[x];
    }
    vector<pair<int, int>> order;
    for (auto [x, c] : count) {
        order.push_back({-c, x});
    }
    sort(order.begin(), order.end());
    if (k < static_cast<int>(order.size()) && order[k - 1].first == order[k].first) return nullopt;
    vector<int> res;
    for (int i = 0; i < k; ++i) {
        res.push_back(order[i].second);
    }
    return res;
}

TEST(examples) {
    run({4, 4, 4, 7, 7, 9}, 2, {4, 7});
    run({3, 0, 3, 0, 3, 5, 0, 0}, 1, {0});
    run({-1}, 1, {-1});
}

TEST(edge_cases) {
    run({2, 2, 2, 2}, 1, {2});
    run({1, 2, 3}, 3, {1, 2, 3});
    run({5, 5, 6, 6, 7}, 2, {5, 6});
    run({1, 1, 1, 2, 2, 3, 3, 4}, 1, {1});
    run({-10000, 10000, 10000, -10000, 0, -10000}, 2, {-10000, 10000});
    run({9, 8, 9, 7, 8, 9, 6, 8, 9}, 2, {9, 8});
}

TEST(random) {
    Rng rng(5);
    for (int done = 0; done < 300;) {
        vector<int> nums = rng.ints(rng(1, 20), -6, 6);
        int distinct = static_cast<int>(set<int>(nums.begin(), nums.end()).size());
        int k = rng(1, distinct);
        if (auto want = brute(nums, k)) {
            run(nums, k, *want);
            ++done;
        }
    }
}

TEST(large) {
    Rng rng(55);
    vector<int> values(20001);
    iota(values.begin(), values.end(), -10000);
    rng.shuffle(values);
    vector<int> nums;
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        nums.insert(nums.end(), i < 100 ? 5 + i : 4, values[i]);
    }
    rng.shuffle(nums);
    run(nums, 100, vector<int>(values.begin(), values.begin() + 100));
    run(nums, 1, {values[99]});
    run(nums, 20001, values);
    nums.assign(50001, 7);
    for (int v : values) {
        if (v != 7 && nums.size() < 70000) {
            nums.push_back(v);
        }
    }
    rng.shuffle(nums);
    run(nums, 1, {7});
}

}
