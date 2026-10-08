#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums1, const vector<int>& nums2, int k, vector<int64_t> want_sums) {
    vector<int> a1 = nums1, a2 = nums2;
    vector<vector<int>> got = Solution().kSmallestPairs(a1, a2, k);
    ensure(static_cast<int>(got.size()) == k, "expected exactly k = " + to_string(k) + " pairs, got " + to_string(got.size()),
           "nums1", nums1, "nums2", nums2, "k", k, "got", got);
    auto count = [](const vector<int>& v, int x) -> int64_t {
        return upper_bound(v.begin(), v.end(), x) - lower_bound(v.begin(), v.end(), x);
    };
    map<pair<int, int>, int64_t> uses;
    vector<int64_t> sums;
    for (auto& p : got) {
        string problem;
        if (p.size() != 2) {
            problem = "every pair must be [u, v]: two numbers, but got " + repr(p);
        } else if (!count(nums1, p[0])) {
            problem = repr(p) + ": " + to_string(p[0]) + " isn't an element of nums1";
        } else if (!count(nums2, p[1])) {
            problem = repr(p) + ": " + to_string(p[1]) + " isn't an element of nums2";
        } else if (++uses[{p[0], p[1]}] > count(nums1, p[0]) * count(nums2, p[1])) {
            problem = repr(p) + " appears more often than there are position pairs (i, j) holding these values";
        }
        if (!problem.empty()) {
            ensure(false, problem, "nums1", nums1, "nums2", nums2, "k", k, "got", got);
        }
        sums.push_back(static_cast<int64_t>(p[0]) + p[1]);
    }
    ensure(sorted(sums) == want_sums, "these pairs don't have the k smallest sums",
           "nums1", nums1, "nums2", nums2, "k", k, "got", got, "got sums", sorted(sums), "want sums", want_sums);
}

static vector<int64_t> smallest_sums_brute(const vector<int>& nums1, const vector<int>& nums2, int k) {
    vector<int64_t> all;
    for (int x : nums1) {
        for (int y : nums2) {
            all.push_back(static_cast<int64_t>(x) + y);
        }
    }
    sort(all.begin(), all.end());
    return vector<int64_t>(all.begin(), all.begin() + k);
}

static vector<int64_t> smallest_sums_large(const vector<int>& nums1, const vector<int>& nums2, int k) {
    vector<int64_t> cand;
    for (int64_t i = 0; i < static_cast<int64_t>(nums1.size()) && i + 1 <= k; ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(nums2.size()) && (i + 1) * (j + 1) <= k; ++j) {
            cand.push_back(static_cast<int64_t>(nums1[i]) + nums2[j]);
        }
    }
    sort(cand.begin(), cand.end());
    return vector<int64_t>(cand.begin(), cand.begin() + k);
}

TEST(examples) {
    run({1, 4, 9}, {2, 3, 8}, 4, {3, 4, 6, 7});
    run({2, 2, 5}, {0, 6}, 3, {2, 2, 5});
    run({0, 1}, {1, 2}, 2, {1, 2});
}

TEST(edge_cases) {
    run({3}, {4}, 1, {7});
    run({1, 2}, {3}, 2, {4, 5});
    run({0}, {1, 2, 3, 4, 5}, 3, {1, 2, 3});
    run({1, 2, 3, 4, 5}, {-1}, 4, {0, 1, 2, 3});
    run({-1000000000, 1000000000}, {-1000000000, 1000000000}, 4, {-2000000000, 0, 0, 2000000000});
    run({5, 5, 5}, {5, 5}, 6, {10, 10, 10, 10, 10, 10});
    run({5, 5, 5}, {5, 5}, 4, {10, 10, 10, 10});
    run({1, 1, 2}, {1, 2, 3}, 3, {2, 2, 3});
    run({1, 1, 2}, {1, 2, 3}, 5, {2, 2, 3, 3, 3});
    run({1, 7, 11}, {2, 4, 6}, 9, {3, 5, 7, 9, 11, 13, 13, 15, 17});
    run({-3, -3, 0}, {-2, 4, 4}, 5, {-5, -5, -2, 1, 1});
}

TEST(random) {
    Rng rng(373);
    for (int t = 0; t < 1500; ++t) {
        int n1 = rng(1, 8), n2 = rng(1, 8), span = rng(0, 1) ? 4 : 1000;
        vector<int> nums1 = sorted(rng.ints(n1, -span, span)), nums2 = sorted(rng.ints(n2, -span, span));
        int k = rng(1, n1 * n2);
        run(nums1, nums2, k, smallest_sums_brute(nums1, nums2, k));
    }
    for (int t = 0; t < 30; ++t) {
        int n1 = rng(1, 120), n2 = rng(1, 120);
        vector<int> nums1 = sorted(rng.ints(n1, -50, 50)), nums2 = sorted(rng.ints(n2, -50, 50));
        int k = rng(1, min(n1 * n2, 10000));
        vector<int64_t> want = smallest_sums_brute(nums1, nums2, k);
        ensure(want == smallest_sums_large(nums1, nums2, k), "test oracle mismatch");
        run(nums1, nums2, k, want);
    }
}

TEST(large) {
    Rng rng(3730);
    const int n = 100000, k = 10000;
    auto big = [&](int lo, int hi) { return sorted(rng.ints(n, lo, hi)); };
    vector<vector<int>> cases1 = {big(-1000000000, 1000000000), vector<int>(n, 0), big(-5, 5), big(0, 1000)};
    vector<vector<int>> cases2 = {big(-1000000000, 1000000000), vector<int>(n, 0), big(-5, 5),
                                  big(-1000000000, -999990000)};
    for (int c = 0; c < 4; ++c) {
        run(cases1[c], cases2[c], k, smallest_sums_large(cases1[c], cases2[c], k));
    }
    vector<int> one = {7};
    vector<int> other = big(-1000000000, 1000000000);
    run(one, other, k, smallest_sums_large(one, other, k));
    run(other, one, k, smallest_sums_large(other, one, k));
}

}
