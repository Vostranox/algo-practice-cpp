#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Intervals = vector<vector<int>>;

static void run(const Intervals& intervals, const vector<int>& queries, const vector<int>& want) {
    Intervals a = intervals;
    vector<int> b = queries;
    check(Solution().minInterval(a, b), want, "intervals", intervals, "queries", queries);
}

static vector<int> brute(const Intervals& intervals, const vector<int>& queries) {
    vector<int> out;
    for (int q : queries) {
        int best = -1;
        for (auto& iv : intervals) {
            if (iv[0] <= q && q <= iv[1] && (best < 0 || iv[1] - iv[0] + 1 < best)) {
                best = iv[1] - iv[0] + 1;
            }
        }
        out.push_back(best);
    }
    return out;
}

TEST(examples) {
    run({{2, 5}, {3, 3}, {1, 8}, {6, 7}}, {3, 6, 9, 1}, {1, 2, -1, 8});
    run({{4, 4}, {10, 20}}, {4, 5, 15, 10}, {1, -1, 11, 11});
}

TEST(edge_cases) {
    run({{1, 1}}, {1}, {1});
    run({{1, 1}}, {2}, {-1});
    run({{1, 10000000}}, {1, 10000000, 5000000}, {10000000, 10000000, 10000000});
    run({{2, 4}, {3, 9}}, {3, 3, 3}, {3, 3, 3});
    run({{2, 4}}, {1, 2, 4, 5}, {-1, 3, 3, -1});
    run({{1, 10}, {3, 7}, {5, 5}}, {5, 4, 8, 1, 7}, {1, 5, 10, 10, 5});
    run({{1, 3}, {2, 4}}, {2, 3}, {3, 3});
    run({{1, 100}, {50, 51}}, {50, 52}, {2, 100});
    run({{1, 2}, {1, 10}, {3, 4}}, {5, 3, 1}, {10, 2, 2});
    run({{5, 8}, {5, 8}, {6, 6}}, {9, 8, 6, 4}, {-1, 4, 1, -1});
}

TEST(random) {
    Rng rng(1851);
    vector<int> spans = {0, 1, 2, 4, 8, 19};
    for (int it = 0; it < 500; ++it) {
        Intervals intervals(rng(1, 8));
        for (auto& iv : intervals) {
            int l = rng(1, 20);
            iv = {l, min(20, l + rng.pick(spans))};
        }
        vector<int> queries = rng.ints(rng(1, 8), 1, 22);
        run(intervals, queries, brute(intervals, queries));
    }
}

TEST(large_nested) {
    const int n = 100000;
    Rng rng(6);
    const int c = 5000000;
    Intervals intervals;
    for (int k = 0; k < n; ++k) {
        intervals.push_back({c - k, c + k});
    }
    rng.shuffle(intervals);
    vector<int> queries = rng.ints(n, c - 3 * n / 2, c + 3 * n / 2), want;
    for (int q : queries) {
        want.push_back(abs(q - c) < n ? 2 * abs(q - c) + 1 : -1);
    }
    run(intervals, queries, want);
}

TEST(large_blocks) {
    const int n = 100000;
    Rng rng(16);
    const int blocks = n / 2;
    vector<int> widths = rng.ints(blocks, 0, 9);
    Intervals intervals;
    for (int i = 0; i < blocks; ++i) {
        intervals.push_back({20 * i + 1, 20 * i + 1 + widths[i]});
    }
    for (int i = 0; i < blocks - 1; ++i) {
        intervals.push_back({20 * i + 1, 20 * i + 15});
    }
    intervals.push_back({1, 1000000});
    rng.shuffle(intervals);
    vector<int> queries = rng.ints(n - 2, 1, 1200000), want;
    queries.push_back(1000000);
    queries.push_back(10000000);
    rng.shuffle(queries);
    for (int q : queries) {
        int i = (q - 1) / 20, off = (q - 1) % 20;
        if (i < blocks && off <= widths[i]) {
            want.push_back(widths[i] + 1);
        } else if (i < blocks - 1 && off <= 14) {
            want.push_back(15);
        } else if (q <= 1000000) {
            want.push_back(1000000);
        } else {
            want.push_back(-1);
        }
    }
    run(intervals, queries, want);
}

}
