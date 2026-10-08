#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Intervals = vector<vector<int>>;

static void run(Intervals intervals, bool want) {
    Intervals arg = intervals;
    check(Solution().canAttendMeetings(arg), want, "intervals", intervals);
}

static bool brute(const Intervals& iv) {
    for (size_t i = 0; i < iv.size(); ++i) {
        for (size_t j = i + 1; j < iv.size(); ++j) {
            if (max(iv[i][0], iv[j][0]) < min(iv[i][1], iv[j][1])) return false;
        }
    }
    return true;
}

TEST(examples) {
    run({{9, 12}, {1, 4}, {5, 8}}, true);
    run({{2, 7}, {6, 9}}, false);
    run({{1, 5}, {5, 6}}, true);
}

TEST(edge_cases) {
    run({}, true);
    run({{0, 1}}, true);
    run({{3, 4}, {1, 3}, {4, 6}}, true);
    run({{1, 10}, {3, 4}}, false);
    run({{1, 2}, {1, 2}}, false);
    run({{0, 1000000}, {999999, 1000000}}, false);
    run({{5, 6}, {0, 1}, {2, 3}, {7, 8}, {1, 2}, {4, 5}}, true);
    run({{5, 6}, {0, 1}, {2, 3}, {7, 8}, {1, 3}, {4, 5}}, false);
}

TEST(random) {
    Rng rng(252);
    for (int it = 0; it < 600; ++it) {
        Intervals iv(rng(0, 7));
        for (auto& v : iv) {
            int s = rng(0, 25);
            v = {s, s + rng(1, 4)};
        }
        run(iv, brute(iv));
    }
}

TEST(large) {
    const int n = 10000;
    Rng rng(1);
    for (int it = 0; it < 4; ++it) {
        set<int> cut_set;
        while (static_cast<int>(cut_set.size()) < n - 1) {
            cut_set.insert(rng(1, 999999));
        }
        vector<int> points = {0};
        points.insert(points.end(), cut_set.begin(), cut_set.end());
        points.push_back(1000000);
        Intervals meetings;
        for (int i = 0; i < n; ++i) {
            meetings.push_back({points[i], points[i + 1]});
        }
        rng.shuffle(meetings);
        run(meetings, true);
        int k = rng(0, n - 2);
        for (auto& m : meetings) {
            if (m[0] == points[k]) {
                ++m[1];
            }
        }
        rng.shuffle(meetings);
        run(meetings, false);
    }
}

}
