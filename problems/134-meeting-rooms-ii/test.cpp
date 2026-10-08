#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Intervals = vector<vector<int>>;

static void run(Intervals intervals, int want) {
    Intervals arg = intervals;
    check(Solution().minMeetingRooms(arg), want, "intervals", intervals);
}

static int brute(const Intervals& iv) {
    int hi = 0, best = 0;
    for (auto& v : iv) {
        hi = max(hi, v[1]);
    }
    for (int t = 0; t < hi; ++t) {
        int running = 0;
        for (auto& v : iv) {
            running += v[0] <= t && t < v[1];
        }
        best = max(best, running);
    }
    return best;
}

TEST(examples) {
    run({{1, 10}, {2, 4}, {5, 9}, {4, 6}}, 3);
    run({{6, 8}, {1, 3}}, 1);
    run({{1, 5}, {5, 10}, {10, 15}}, 1);
}

TEST(edge_cases) {
    run({{0, 1}}, 1);
    run({{1, 2}, {1, 2}}, 2);
    run({{1, 3}, {2, 4}}, 2);
    run({{1, 3}, {3, 4}, {2, 3}}, 2);
    run({{0, 1000000}, {0, 1000000}, {5, 6}}, 3);
    run({{1, 4}, {4, 7}, {2, 5}, {5, 8}, {3, 6}}, 3);
    run({{1, 2}, {2, 3}, {3, 4}, {1, 4}}, 2);
    run({{1, 100}, {2, 3}, {4, 5}, {6, 7}, {8, 9}}, 2);
    run({{3, 5}, {0, 10}, {1, 4}, {2, 3}, {4, 6}}, 3);
}

TEST(random) {
    Rng rng(253);
    for (int it = 0; it < 500; ++it) {
        Intervals iv(rng(1, 8));
        for (auto& v : iv) {
            int s = rng(0, 20);
            v = {s, s + rng(1, 6)};
        }
        run(iv, brute(iv));
    }
}

TEST(large) {
    const int n = 10000;
    Rng rng(2);
    Intervals nested;
    for (int i = 0; i < n; ++i) {
        nested.push_back({i, 1000000 - i});
    }
    rng.shuffle(nested);
    run(nested, n);
    for (int k : {1, 2, 5, 40, 625}) {
        Intervals meetings;
        for (int track = 0; track < k; ++track) {
            set<int> cut_set;
            while (static_cast<int>(cut_set.size()) < n / k - 1) {
                cut_set.insert(rng(1, 999999));
            }
            vector<int> points = {0};
            points.insert(points.end(), cut_set.begin(), cut_set.end());
            points.push_back(1000000);
            for (int i = 0; i < n / k; ++i) {
                meetings.push_back({points[i], points[i + 1]});
            }
        }
        rng.shuffle(meetings);
        run(meetings, k);
    }
    Intervals pairs;
    for (int j = 0; j < n / 2; ++j) {
        pairs.push_back({100 * j, 100 * j + 60});
        pairs.push_back({100 * j + 40, 100 * j + 100});
    }
    rng.shuffle(pairs);
    run(pairs, 2);
}

}
