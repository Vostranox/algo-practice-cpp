#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Intervals = vector<vector<int>>;

static void run(const Intervals& intervals, int want) {
    Intervals arg = intervals;
    check(Solution().eraseOverlapIntervals(arg), want, "intervals", intervals);
}

static bool overlap(const vector<int>& a, const vector<int>& b) {
    return max(a[0], b[0]) < min(a[1], b[1]);
}

static int brute(const Intervals& iv) {
    int n = static_cast<int>(iv.size()), best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        for (int i = 0; i < n && ok; ++i) {
            for (int j = i + 1; j < n && ok; ++j) {
                if ((mask >> i & 1) && (mask >> j & 1) && overlap(iv[i], iv[j])) {
                    ok = false;
                }
            }
        }
        if (ok) {
            best = max(best, __builtin_popcount(mask));
        }
    }
    return n - best;
}

TEST(examples) {
    run({{1, 3}, {2, 4}, {3, 5}, {1, 5}}, 2);
    run({{0, 2}, {2, 4}, {4, 6}}, 0);
    run({{5, 9}, {5, 9}, {5, 9}}, 2);
}

TEST(edge_cases) {
    run({{0, 1}}, 0);
    run({{1, 2}, {2, 3}}, 0);
    run({{2, 3}, {1, 2}}, 0);
    run({{1, 3}, {2, 4}}, 1);
    run({{1, 10}, {2, 3}, {4, 5}, {6, 7}}, 1);
    run({{1, 4}, {2, 3}}, 1);
    run({{-50000, 50000}, {-1, 0}, {0, 1}}, 1);
    run({{1, 2}, {1, 2}, {2, 3}, {2, 3}}, 2);
    run({{0, 5}, {1, 2}, {2, 3}, {3, 4}, {4, 6}}, 1);
    run({{1, 5}, {2, 6}, {3, 7}, {4, 8}, {5, 9}}, 3);
}

TEST(random) {
    Rng rng(435);
    for (int it = 0; it < 500; ++it) {
        Intervals iv(rng(1, 9));
        for (auto& v : iv) {
            int s = rng(-6, 6);
            v = {s, s + rng(1, 5)};
        }
        run(iv, brute(iv));
    }
}

const int n = 100000, lo = -50000, hi = 50000;

TEST(large) {
    Rng rng(10);
    Intervals chain;
    for (int x = lo; x < hi; ++x) {
        chain.push_back({x, x + 1});
    }
    rng.shuffle(chain);
    run(chain, 0);
    Intervals crowd(n);
    for (auto& v : crowd) {
        v = {rng(lo, 0), rng(1, hi)};
    }
    run(crowd, n - 1);
}

TEST(large_slots) {
    Rng rng(11);
    Intervals slots;
    int want = 0;
    for (int k = 0; k < n / 4; ++k) {
        Intervals local(4);
        for (auto& v : local) {
            int s = rng(0, 3);
            v = {s, rng(s + 1, 4)};
        }
        want += brute(local);
        for (auto& v : local) {
            slots.push_back({lo + 4 * k + v[0], lo + 4 * k + v[1]});
        }
    }
    rng.shuffle(slots);
    run(slots, want);
}

}
