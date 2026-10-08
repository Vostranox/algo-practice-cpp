#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, int want) {
    vector<int> arg = nums;
    check(Solution().findMin(arg), want, "nums", nums);
}

static vector<int> rotate_times(const vector<int>& sorted_nums, int r) {
    int n = sorted_nums.size();
    r %= n;
    vector<int> out(sorted_nums.end() - r, sorted_nums.end());
    out.insert(out.end(), sorted_nums.begin(), sorted_nums.end() - r);
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
    run({8, 11, 15, 2, 5}, 2);
    run({-4, 0, 3, 9}, -4);
    run({6, 1}, 1);
}

TEST(edge_cases) {
    run({7}, 7);
    run({-5000}, -5000);
    run({1, 6}, 1);
    run({2, 3, 1}, 1);
    run({3, 1, 2}, 1);
    run({1, 2, 3}, 1);
    run({5, -5000, 0, 1, 2, 3, 4}, -5000);
    run({-1, 0, 1, 2, 3, 4, 5000, -2}, -2);
    run({5000, -5000}, -5000);
}

TEST(every_rotation) {
    Rng rng(31);
    for (int n = 1; n <= 40; ++n) {
        for (int rep = 0; rep < 3; ++rep) {
            vector<int> base = distinct_sorted(rng, n, -5000, 5000);
            for (int r = 0; r < n; ++r) {
                run(rotate_times(base, r), base[0]);
            }
        }
    }
    vector<int> base = distinct_sorted(rng, 5000, -5000, 5000);
    for (int r = 0; r < 5000; r += 7) {
        run(rotate_times(base, r), base[0]);
    }
    run(rotate_times(base, 4999), base[0]);
}

TEST(many_calls) {
    const int n = 5000;
    Rng rng(153);
    vector<int> base = distinct_sorted(rng, n, -5000, 5000);
    vector<vector<int>> rotated, args;
    for (int k = 0; k < 16; ++k) {
        rotated.push_back(rotate_times(base, k == 0 ? 1 : k * n / 16 + rng(0, n / 16 - 1)));
    }
    args = rotated;
    for (int q = 0; q < 1600000; ++q) {
        vector<int>& arg = args[q % 16];
        int got = Solution().findMin(arg);
        if (got != base[0]) {
            check(got, base[0], "nums", rotated[q % 16]);
        }
        if (arg.size() != static_cast<size_t>(n)) {
            fail("findMin() must not modify nums");
        }
    }
    ensure(args == rotated, "findMin() must not modify nums");
}

}
