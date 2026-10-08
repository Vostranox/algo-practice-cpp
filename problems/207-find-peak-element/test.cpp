#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static bool is_peak(const vector<int>& nums, int i) {
    int n = nums.size();
    return i >= 0 && i < n && (i == 0 || nums[i - 1] < nums[i]) && (i == n - 1 || nums[i + 1] < nums[i]);
}

static void run(const vector<int>& nums) {
    vector<int> arg = nums;
    int got = Solution().findPeakElement(arg);
    ensure(is_peak(nums, got), "the returned index is not a peak (or is out of range)", "nums", nums, "got", got);
}

static void run(const vector<int>& nums, int want) {
    vector<int> arg = nums;
    check(Solution().findPeakElement(arg), want, "nums", nums);
}

static vector<int> no_equal_neighbours(Rng& rng, int n, int64_t lo, int64_t hi) {
    vector<int> v;
    while (static_cast<int>(v.size()) < n) {
        int x = rng.range(lo, hi);
        if (v.empty() || v.back() != x) {
            v.push_back(x);
        }
    }
    return v;
}

static vector<int> mountain(int n, int peak, int top) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = top - abs(i - peak);
    }
    return v;
}

TEST(examples) {
    run({2, 7, 4, 1}, 1);
    run({1, 5, 3, 4, 8, 6});
    run({9, 6, 2}, 0);
}

TEST(edge_cases) {
    run({5}, 0);
    run({INT_MIN}, 0);
    run({1, 2}, 1);
    run({2, 1}, 0);
    run({INT_MIN, INT_MIN + 1}, 1);
    run({INT_MIN + 1, INT_MIN}, 0);
    run({INT_MAX, INT_MIN}, 0);
    run({INT_MIN, INT_MAX}, 1);
    run({INT_MIN, INT_MAX, INT_MIN}, 1);
    run({INT_MAX, INT_MIN, INT_MAX});
    run({1, 2, 3, 4, 5, 6, 7}, 6);
    run({7, 6, 5, 4, 3, 2, 1}, 0);
    run({1, 3, 1, 3, 1, 3, 1});
    run({3, 1, 3, 1, 3, 1, 3});
    run({-1, -5, -2, -8, -3});
}

TEST(random) {
    Rng rng(162);
    for (int i = 0; i < 3000; ++i) {
        int n = rng(1, 30);
        run(no_equal_neighbours(rng, n, -4, 4));
    }
    for (int i = 0; i < 300; ++i) {
        run(no_equal_neighbours(rng, rng(1, 1000), INT_MIN, INT_MAX));
    }
    for (int i = 0; i < 300; ++i) {
        int n = rng(1, 1000), peak = rng(0, n - 1);
        run(mountain(n, peak, rng(1000, 5000)), peak);
    }
}

TEST(many_calls) {
    const int n = 1000;
    Rng rng(1620);
    vector<vector<int>> arrays;
    vector<int> peaks;
    for (int k = 0; k < 16; ++k) {
        peaks.push_back(rng(650, 950));
        arrays.push_back(mountain(n, peaks.back(), rng(INT_MIN + 2000, INT_MAX - 1)));
    }
    vector<vector<int>> args = arrays;
    for (int q = 0; q < 4000000; ++q) {
        vector<int>& arg = args[q & 15];
        int got = Solution().findPeakElement(arg);
        if (got != peaks[q & 15]) {
            check(got, peaks[q & 15], "nums", arrays[q & 15]);
        }
        if (arg.size() != static_cast<size_t>(n)) {
            fail("findPeakElement() must not modify nums");
        }
    }
    ensure(args == arrays, "findPeakElement() must not modify nums");
}

}
