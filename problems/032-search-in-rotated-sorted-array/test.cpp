#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int target, int want) {
    vector<int> arg = nums;
    check(Solution().search(arg, target), want, "nums", nums, "target", target);
}

static int oracle(const vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == target) return static_cast<int>(i);
    }
    return -1;
}

static vector<int> rotate_at(const vector<int>& sorted_nums, int k) {
    vector<int> out(sorted_nums.begin() + k, sorted_nums.end());
    out.insert(out.end(), sorted_nums.begin(), sorted_nums.begin() + k);
    return out;
}

static vector<int> distinct_sorted(Rng& rng, int n, int lo, int hi) {
    vector<int> all(hi - lo + 1);
    iota(all.begin(), all.end(), lo);
    rng.shuffle(all);
    all.resize(n);
    return sorted(all);
}

TEST(examples) {
    run({12, 15, 19, 1, 4, 7}, 4, 4);
    run({12, 15, 19, 1, 4, 7}, 13, -1);
    run({3, 5, 8}, 3, 0);
}

TEST(edge_cases) {
    run({5}, 5, 0);
    run({5}, 4, -1);
    run({5}, 6, -1);
    run({2, 1}, 1, 1);
    run({2, 1}, 2, 0);
    run({2, 1}, 3, -1);
    run({2, 1}, 0, -1);
    run({1, 2}, 2, 1);
    run({12, 15, 19, 1, 4, 7}, 12, 0);
    run({12, 15, 19, 1, 4, 7}, 7, 5);
    run({12, 15, 19, 1, 4, 7}, 19, 2);
    run({12, 15, 19, 1, 4, 7}, 1, 3);
    run({12, 15, 19, 1, 4, 7}, 10, -1);
    run({12, 15, 19, 1, 4, 7}, 20, -1);
    run({12, 15, 19, 1, 4, 7}, 0, -1);
    run({10000, -10000}, -10000, 1);
}

TEST(every_rotation_and_target) {
    Rng rng(32);
    for (int n = 1; n <= 16; ++n) {
        for (int rep = 0; rep < 3; ++rep) {
            vector<int> base = distinct_sorted(rng, n, -40, 40);
            for (int k = 0; k < n; ++k) {
                vector<int> nums = rotate_at(base, k);
                for (int target = base[0] - 2; target <= base.back() + 2; ++target) {
                    run(nums, target, oracle(nums, target));
                }
            }
        }
    }
    vector<int> base = distinct_sorted(rng, 5000, -10000, 10000);
    for (int k : {0, 1, 2500, 4999, rng(0, 4999)}) {
        vector<int> nums = rotate_at(base, k), arg = nums;
        vector<int> index_of(20001, -1);
        for (int i = 0; i < 5000; ++i) {
            index_of[nums[i] + 10000] = i;
        }
        for (int target = -10000; target <= 10000; ++target) {
            check(Solution().search(arg, target), index_of[target + 10000], "nums", nums, "target", target);
        }
        ensure(arg == nums, "search() must not modify nums");
    }
}

TEST(many_searches) {
    const int n = 5000;
    Rng rng(33);
    vector<int> base = distinct_sorted(rng, n, -10000, 10000);
    vector<vector<int>> rotated, args;
    vector<vector<int>> index_of;
    for (int k = 0; k < 16; ++k) {
        rotated.push_back(rotate_at(base, k == 0 ? 0 : k * n / 16 + rng(0, n / 16 - 1)));
        index_of.emplace_back(20001, -1);
        for (int i = 0; i < n; ++i) {
            index_of.back()[rotated.back()[i] + 10000] = i;
        }
    }
    args = rotated;
    for (int q = 0; q < 1600000; ++q) {
        int which = q % 16, target = rng(-10000, 10000), want = index_of[which][target + 10000];
        vector<int>& arg = args[which];
        int got = Solution().search(arg, target);
        if (got != want) {
            check(got, want, "nums", rotated[which], "target", target);
        }
        if (arg.size() != static_cast<size_t>(n)) {
            fail("search() must not modify nums");
        }
    }
    ensure(args == rotated, "search() must not modify nums");
}

}
