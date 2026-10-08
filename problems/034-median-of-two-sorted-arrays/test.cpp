#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static double median(const vector<int>& a, const vector<int>& b) {
    vector<int> all = a;
    all.insert(all.end(), b.begin(), b.end());
    sort(all.begin(), all.end());
    size_t k = all.size();
    return k % 2 ? all[k / 2] : (static_cast<double>(all[k / 2 - 1]) + all[k / 2]) / 2;
}

static void run(const vector<int>& nums1, const vector<int>& nums2, double want) {
    vector<int> a = nums1, b = nums2;
    check_close(Solution().findMedianSortedArrays(a, b), want, "nums1", nums1, "nums2", nums2);
}

TEST(examples) {
    run({1, 4, 9}, {2, 3}, 3.0);
    run({5, 6}, {1, 2, 10, 12}, 5.5);
    run({}, {-3, -1}, -2.0);
}

TEST(edge_cases) {
    run({}, {1}, 1.0);
    run({2}, {}, 2.0);
    run({1}, {2}, 1.5);
    run({2}, {1}, 1.5);
    run({}, {1, 2, 3, 4}, 2.5);
    run({7, 8, 9}, {}, 8.0);
    run({1, 2}, {3, 4}, 2.5);
    run({3, 4}, {1, 2}, 2.5);
    run({1, 3}, {2}, 2.0);
    run({1, 1, 1}, {1, 1}, 1.0);
    run({0, 0, 0, 0, 0}, {-1, 0, 0, 0, 0, 0, 1}, 0.0);
    run({-1000000}, {1000000}, 0.0);
    run({1000000, 1000000}, {1000000}, 1e6);
    run({-1000000, -999999}, {-1000000}, -1e6);
    run({999999, 1000000}, {1000000, 1000000}, 1e6);
    run({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {5}, 5.0);
    run({-5, 3, 6, 12, 15}, {-12, -10, -6, -3, 4, 10}, 3.0);
    run({4}, {1, 2, 3, 5, 6, 7}, 4.0);
    run({1, 2, 3, 5, 6, 7}, {4}, 4.0);
    run({2, 3}, {1, 4, 5, 6}, 3.5);
}

TEST(random) {
    Rng rng(4);
    for (int iter = 0; iter < 5000; ++iter) {
        int m = rng(0, 9), n = rng(0, 9);
        if (m + n == 0) continue;
        int spread = rng.pick(vector<int>{3, 20, 1000000});
        vector<int> a = sorted(rng.ints(m, -spread, spread)), b = sorted(rng.ints(n, -spread, spread));
        run(a, b, median(a, b));
    }
}

TEST(large) {
    Rng rng(44);
    auto values = [&](int k, int lo = -1000000, int hi = 1000000) { return sorted(rng.ints(k, lo, hi)); };
    vector<pair<vector<int>, vector<int>>> cases = {
        {values(1000), values(1000)},
        {values(1000), values(999)},
        {values(999), values(1000)},
        {{}, values(1000)},
        {values(1000), {}},
        {{}, values(999)},
        {values(1), values(1000)},
        {values(1000), values(2)},
        {values(300), values(1000)},
        {values(1000, -1000000, -1), values(1000, 0, 1000000)},
        {values(1000, 0, 1000000), values(999, -1000000, -1)},
        {values(20, -100, 100), values(1000)},
        {vector<int>(1000, 5), vector<int>(1000, 5)},
        {vector<int>(1000, 1000000), vector<int>(1000, 1000000)},
        {vector<int>(1000, -1000000), vector<int>(1000, -1000000)},
    };
    for (int iter = 0; iter < 200; ++iter) {
        int m = rng(0, 1000), n = rng(m == 0 ? 1 : 0, 1000);
        int spread = rng.pick(vector<int>{5, 1000, 1000000});
        cases.push_back({values(m, -spread, spread), values(n, -spread, spread)});
    }
    for (auto& [a, b] : cases) {
        run(a, b, median(a, b));
    }
}

}
