#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> height, int want) {
    vector<int> arg = height;
    check(Solution().trap(arg), want, "height", height);
}

static int brute(const vector<int>& h) {
    int64_t total = 0;
    int n = h.size();
    for (int i = 0; i < n; ++i) {
        int left = *max_element(h.begin(), h.begin() + i + 1);
        int right = *max_element(h.begin() + i, h.end());
        total += min(left, right) - h[i];
    }
    return static_cast<int>(total);
}

static int oracle(const vector<int>& h) {
    int n = h.size();
    vector<int> left(n), right(n);
    for (int i = 0, m = 0; i < n; ++i) {
        left[i] = m = max(m, h[i]);
    }
    for (int i = n - 1, m = 0; i >= 0; --i) {
        right[i] = m = max(m, h[i]);
    }
    int64_t total = 0;
    for (int i = 0; i < n; ++i) {
        total += min(left[i], right[i]) - h[i];
    }
    return static_cast<int>(total);
}

TEST(examples) {
    run({3, 0, 2, 0, 4}, 7);
    run({5, 4, 1, 2}, 1);
    run({1, 2, 3}, 0);
}

TEST(edge_cases) {
    run({0}, 0);
    run({7}, 0);
    run({3, 3}, 0);
    run({0, 0, 0}, 0);
    run({3, 0, 3}, 3);
    run({2, 0, 5}, 2);
    run({6, 0, 2}, 2);
    run({5, 0, 0, 0, 5}, 15);
    run({4, 1, 1, 4}, 6);
    run({4, 1, 4, 1, 4}, 6);
    run({100000, 0, 100000}, 100000);
    run({5, 4, 3, 2, 1}, 0);
    run({0, 3, 1, 2, 0, 4, 1, 1, 3}, 10);
}

TEST(random) {
    Rng rng(14);
    for (int i = 0; i < 300; ++i) {
        vector<int> height = rng.ints(rng(1, 15), 0, 8);
        run(height, brute(height));
    }
}

TEST(large) {
    Rng rng(1414);
    const int n = 20000, H = 100000;
    vector<int> walls(n, 0);
    walls.front() = walls.back() = H;
    run(walls, H * (n - 2));
    vector<int> peak;
    for (int i = 0; i < n / 2; ++i) {
        peak.push_back(i);
    }
    for (int i = n / 2; i > 0; --i) {
        peak.push_back(i);
    }
    run(peak, 0);
    vector<int> valley;
    for (int i = 10000; i > 0; --i) {
        valley.push_back(i);
    }
    for (int i = 0; i < 10000; ++i) {
        valley.push_back(i);
    }
    run(valley, 9998 * 9999 / 2 + 9999 * 10000 / 2);
    for (int c = 0; c < 3; ++c) {
        vector<int> height = rng.ints(n, 0, H);
        run(height, oracle(height));
    }
}

}
