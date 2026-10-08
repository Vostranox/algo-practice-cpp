#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int target, vector<int> want) {
    vector<int> arg = nums;
    check(Solution().searchRange(arg, target), want, "nums", nums, "target", target);
}

static vector<int> oracle(const vector<int>& nums, int target) {
    int first = -1, last = -1;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (nums[i] == target) {
            if (first < 0) {
                first = i;
            }
            last = i;
        }
    }
    return {first, last};
}

TEST(examples) {
    run({1, 3, 3, 3, 6, 9}, 3, {1, 3});
    run({1, 3, 3, 3, 6, 9}, 4, {-1, -1});
    run({}, 0, {-1, -1});
}

TEST(edge_cases) {
    run({5}, 5, {0, 0});
    run({5}, 4, {-1, -1});
    run({5}, 6, {-1, -1});
    run({2, 2}, 2, {0, 1});
    run({2, 2, 2, 2, 2}, 2, {0, 4});
    run({2, 2, 2, 2, 2}, 3, {-1, -1});
    run({1, 2, 2, 2}, 2, {1, 3});
    run({2, 2, 2, 3}, 2, {0, 2});
    run({1, 2, 3}, 1, {0, 0});
    run({1, 2, 3}, 3, {2, 2});
    run({1, 2, 3}, 0, {-1, -1});
    run({1, 2, 3}, 4, {-1, -1});
    run({1, 1, 3, 3}, 2, {-1, -1});
    run({-1000000000, -1000000000, 1000000000}, -1000000000, {0, 1});
    run({-1000000000, 1000000000, 1000000000}, 1000000000, {1, 2});
    run({-1000000000, 1000000000}, 0, {-1, -1});
    run({7, 7, 7}, -1000000000, {-1, -1});
    run({7, 7, 7}, 1000000000, {-1, -1});
}

TEST(every_target) {
    Rng rng(34);
    for (int i = 0; i < 400; ++i) {
        int n = rng(0, 40), lo = rng(-20, 0);
        vector<int> nums = sorted(rng.ints(n, lo, lo + rng(0, 10)));
        for (int target = lo - 2; target <= lo + 12; ++target) {
            run(nums, target, oracle(nums, target));
        }
    }
    for (int i = 0; i < 5; ++i) {
        vector<int> nums = sorted(rng.ints(100000, -1000000000, 1000000000));
        for (int k = 0; k < 20; ++k) {
            int target = rng.coin() ? rng.pick(nums) : rng(-1000000000, 1000000000);
            run(nums, target, oracle(nums, target));
        }
    }
}

TEST(many_searches) {
    struct Arr {
        vector<int> nums;
        vector<array<int, 3>> runs;
    };
    vector<Arr> arrs;
    for (vector<int> lengths : {vector<int>{100000}, vector<int>{1, 30000, 1, 40000, 29998}, vector<int>(1000, 100)}) {
        Arr a;
        int value = -999999999;
        for (int len : lengths) {
            a.runs.push_back({value, static_cast<int>(a.nums.size()), static_cast<int>(a.nums.size()) + len - 1});
            a.nums.insert(a.nums.end(), len, value);
            value += 2000000;
        }
        arrs.push_back(a);
    }
    Rng rng(340);
    vector<vector<int>> args;
    for (auto& a : arrs) {
        args.push_back(a.nums);
    }
    for (int q = 0; q < 300000; ++q) {
        int which = q % 3;
        const Arr& a = arrs[which];
        auto [target, first, last] = rng.pick(a.runs);
        if (q % 10 == 9) {
            target += rng.coin() ? 1 : -1;
            first = last = -1;
        }
        vector<int> got = Solution().searchRange(args[which], target);
        if (got.size() != 2 || got[0] != first || got[1] != last) {
            check(got, {first, last}, "nums", a.nums, "target", target);
        }
    }
    for (int i = 0; i < 3; ++i) {
        ensure(args[i] == arrs[i].nums, "searchRange() must not modify nums");
    }
}

}
