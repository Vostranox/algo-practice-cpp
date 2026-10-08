#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Points = vector<vector<int>>;

static void run(const Points& points, int want) {
    Points arg = points;
    check(Solution().findMinArrowShots(arg), want, "points", points);
}

static int brute(const Points& p) {
    int n = p.size(), best = n;
    for (int mask = 1; mask < (1 << n); ++mask) {
        int arrows = __builtin_popcount(mask);
        if (arrows >= best) continue;
        bool all_hit = true;
        for (int b = 0; b < n && all_hit; ++b) {
            bool hit = false;
            for (int a = 0; a < n && !hit; ++a) {
                if (mask >> a & 1) {
                    hit = p[b][0] <= p[a][1] && p[a][1] <= p[b][1];
                }
            }
            all_hit = hit;
        }
        if (all_hit) {
            best = arrows;
        }
    }
    return best;
}

TEST(examples) {
    run({{3, 7}, {1, 4}, {8, 12}, {6, 9}}, 2);
    run({{1, 2}, {3, 4}, {5, 6}}, 3);
    run({{1, 3}, {3, 5}, {5, 7}}, 2);
}

TEST(edge_cases) {
    run({{0, 1}}, 1);
    run({{1, 2}, {2, 3}}, 1);
    run({{2, 3}, {1, 2}}, 1);
    run({{1, 10}, {2, 3}, {4, 5}}, 2);
    run({{-5, -1}, {-3, 2}, {1, 4}}, 2);
    run({{2, 3}, {2, 3}, {2, 3}}, 1);
    run({{1, 5}, {2, 6}, {3, 7}, {6, 8}}, 2);
    run({{1, 2}, {4, 5}, {1, 5}, {2, 4}}, 2);
    run({{0, 9}, {1, 8}, {2, 7}, {3, 6}, {4, 5}}, 1);
}

TEST(int_limits) {
    run({{INT_MIN, INT_MAX}}, 1);
    run({{INT_MIN, INT_MAX}, {INT_MIN, INT_MAX}}, 1);
    run({{INT_MIN, -1}, {0, INT_MAX}}, 2);
    run({{0, INT_MAX}, {INT_MIN, -1}}, 2);
    run({{INT_MAX - 1, INT_MAX}, {INT_MIN, INT_MIN + 1}}, 2);
    run({{INT_MIN, 0}, {0, INT_MAX}}, 1);
    run({{INT_MIN, INT_MIN + 1}, {INT_MIN + 1, INT_MAX}, {INT_MAX - 1, INT_MAX}}, 2);
}

TEST(random) {
    Rng rng(452);
    const vector<int> extreme = {INT_MIN, INT_MIN + 1, -1, 0, 1, INT_MAX - 1, INT_MAX};
    for (int it = 0; it < 1000; ++it) {
        Points p(rng(1, 9));
        for (auto& b : p) {
            int x, y;
            do {
                x = it % 2 ? rng.pick(extreme) : rng(-6, 6);
                y = it % 2 ? rng.pick(extreme) : rng(-6, 6);
            } while (x == y);
            b = {min(x, y), max(x, y)};
        }
        run(p, brute(p));
    }
}

const int n = 100000;

TEST(large) {
    Rng rng(45200);
    Points apart(n);
    for (int i = 0; i < n; ++i) {
        int64_t start = INT_MIN + int64_t{42949} * i;
        apart[i] = {static_cast<int>(start), i == n - 1 ? INT_MAX : static_cast<int>(start + 42948)};
    }
    rng.shuffle(apart);
    run(apart, n);
    Points chain(n);
    for (int i = 0; i < n; ++i) {
        chain[i] = {i, i + 1};
    }
    rng.shuffle(chain);
    run(chain, n / 2);
    Points crowd(n);
    for (auto& b : crowd) {
        b = {rng(INT_MIN, 0), rng(1, INT_MAX)};
    }
    run(crowd, 1);
}

TEST(large_slots) {
    Rng rng(45201);
    const int slots = n / 4, step = 24542;
    auto coord = [&](int slot, int c) {
        int64_t pos = slot * int64_t{7} + c;
        return pos == slots * int64_t{7} - 1 ? INT_MAX : static_cast<int>(INT_MIN + pos * step);
    };
    Points all;
    int want = 0;
    for (int k = 0; k < slots; ++k) {
        Points local(4);
        for (auto& b : local) {
            int x = rng(0, 5);
            b = {x, rng(x + 1, 6)};
        }
        want += brute(local);
        for (auto& b : local) {
            all.push_back({coord(k, b[0]), coord(k, b[1])});
        }
    }
    rng.shuffle(all);
    run(all, want);
}

}
