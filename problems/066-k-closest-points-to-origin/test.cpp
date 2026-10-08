#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<vector<int>> points, int k, vector<vector<int>> want) {
    vector<vector<int>> arg = points;
    auto got = Solution().kClosest(arg, k);
    for (auto& p : got) {
        ensure(p.size() == 2, "every returned point should be an [x, y] pair", "points", points, "k", k, "got", got);
    }
    check(sorted(got), sorted(want), "points", points, "k", k);
}

static int d2(const vector<int>& p) { return p[0] * p[0] + p[1] * p[1]; }

static bool closest_by_sort(const vector<vector<int>>& points, int k, vector<vector<int>>& out) {
    vector<vector<int>> by = points;
    stable_sort(by.begin(), by.end(), [](auto& a, auto& b) { return d2(a) < d2(b); });
    if (k < static_cast<int>(by.size()) && d2(by[k - 1]) == d2(by[k])) return false;
    out.assign(by.begin(), by.begin() + k);
    return true;
}

TEST(examples) {
    run({{2, -1}, {0, 3}, {-1, -1}}, 2, {{-1, -1}, {2, -1}});
    run({{4, 4}, {-5, 0}, {1, -6}, {3, -2}}, 1, {{3, -2}});
    run({{1, 2}, {2, 1}, {5, 5}}, 2, {{1, 2}, {2, 1}});
}

TEST(edge_cases) {
    run({{7, -7}}, 1, {{7, -7}});
    run({{0, 0}, {3, 3}, {-1, 2}}, 3, {{0, 0}, {3, 3}, {-1, 2}});
    run({{10000, 10000}, {-10000, -10000}, {0, 0}}, 1, {{0, 0}});
    run({{10000, -10000}, {-9999, 10000}, {10000, 9999}}, 2, {{-9999, 10000}, {10000, 9999}});
    run({{1, 1}, {1, 1}, {3, 0}}, 2, {{1, 1}, {1, 1}});
    run({{0, 5}, {5, 0}, {-3, -4}, {4, 3}, {6, 0}}, 4, {{0, 5}, {5, 0}, {-3, -4}, {4, 3}});
    run({{-2, 0}, {0, -2}, {1, 1}}, 1, {{1, 1}});
}

TEST(random) {
    Rng rng(973);
    for (int done = 0; done < 1000;) {
        int n = rng(1, 12);
        vector<vector<int>> points;
        for (int i = 0; i < n; ++i) {
            points.push_back({rng(-6, 6), rng(-6, 6)});
        }
        int k = rng(1, n);
        vector<vector<int>> want;
        if (!closest_by_sort(points, k, want)) continue;
        run(points, k, want);
        ++done;
    }
}

TEST(large) {
    Rng rng(9730);
    for (int k : {1, 5000, 10000}) {
        for (;;) {
            vector<vector<int>> points;
            for (int i = 0; i < 10000; ++i) {
                points.push_back({rng(-10000, 10000), rng(-10000, 10000)});
            }
            vector<vector<int>> want;
            if (!closest_by_sort(points, k, want)) continue;
            run(points, k, want);
            break;
        }
    }
}

}
