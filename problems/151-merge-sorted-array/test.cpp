#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums1, int m, const vector<int>& nums2, int n, const vector<int>& want) {
    vector<int> a = nums1, b = nums2;
    Solution().merge(a, m, b, n);
    check(a, want, "nums1", nums1, "m", m, "nums2", nums2, "n", n);
}

static vector<int> merged(const vector<int>& real, const vector<int>& nums2) {
    vector<int> all = real;
    all.insert(all.end(), nums2.begin(), nums2.end());
    return sorted(all);
}

static void run(const vector<int>& real, const vector<int>& nums2) {
    vector<int> nums1 = real;
    nums1.resize(real.size() + nums2.size(), 0);
    run(nums1, static_cast<int>(real.size()), nums2, static_cast<int>(nums2.size()), merged(real, nums2));
}

TEST(examples) {
    run({2, 5, 9, 0, 0}, 3, {4, 10}, 2, {2, 4, 5, 9, 10});
    run({0, 0, 0}, 0, {-3, 1, 1}, 3, {-3, 1, 1});
    run({7}, 1, {}, 0, {7});
}

TEST(edge_cases) {
    run({0}, 0, {5}, 1, {5});
    run({1, 2, 3, 0, 0, 0}, 3, {4, 5, 6}, 3, {1, 2, 3, 4, 5, 6});
    run({4, 5, 6, 0, 0, 0}, 3, {1, 2, 3}, 3, {1, 2, 3, 4, 5, 6});
    run({1, 5, 9, 0, 0, 0}, 3, {2, 6, 10}, 3, {1, 2, 5, 6, 9, 10});
    run({2, 2, 0, 0}, 2, {2, 2}, 2, {2, 2, 2, 2});
    run({0, 0, 0}, 1, {-5, -2}, 2, {-5, -2, 0});
    run({-1, 0, 0}, 1, {0, 0}, 2, {-1, 0, 0});
    run({3, 0}, 1, {1}, 1, {1, 3});
    run({-1000000000, 1000000000, 0, 0}, 2, {-1000000000, 1000000000}, 2,
        {-1000000000, -1000000000, 1000000000, 1000000000});
}

TEST(random) {
    Rng rng(88);
    for (int it = 0; it < 500; ++it) {
        int m = rng(0, 10), n = rng(m == 0 ? 1 : 0, 10);
        run(sorted(rng.ints(m, -5, 5)), sorted(rng.ints(n, -5, 5)));
    }
}

TEST(large) {
    Rng rng(8800);
    const int lim = 1000000000;
    for (int m : {200, 0, 100, 1, 199, 37}) {
        int n = 200 - m;
        run(sorted(rng.ints(m, -lim, lim)), sorted(rng.ints(n, -lim, lim)));
    }
    vector<int> evens, odds;
    for (int i = 0; i < 100; ++i) {
        evens.push_back(2 * i), odds.push_back(2 * i + 1);
    }
    run(evens, odds);
    run(odds, evens);
}

}
