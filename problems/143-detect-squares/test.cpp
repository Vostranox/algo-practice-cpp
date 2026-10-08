#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using P = vector<int>;

using Pt = pair<int, int>;

static bool is_square(array<Pt, 4> c) {
    auto [xl, xh] = minmax({c[0].first, c[1].first, c[2].first, c[3].first});
    auto [yl, yh] = minmax({c[0].second, c[1].second, c[2].second, c[3].second});
    if (xl == xh || xh - xl != yh - yl) return false;
    sort(c.begin(), c.end());
    return c == array<Pt, 4>{Pt{xl, yl}, Pt{xl, yh}, Pt{xh, yl}, Pt{xh, yh}};
}

static int brute_count(const vector<Pt>& stored, Pt q) {
    int total = 0, n = stored.size();
    for (int a = 0; a < n; ++a) {
        for (int b = a + 1; b < n; ++b) {
            for (int c = b + 1; c < n; ++c) {
                total += is_square({q, stored[a], stored[b], stored[c]});
            }
        }
    }
    return total;
}

struct SideOracle {
    map<pair<int, int>, int64_t> cnt;
    map<int, map<int, int64_t>> col;
    void add(int x, int y) { ++cnt[{x, y}], ++col[x][y]; }
    int64_t get(int x, int y) const {
        auto it = cnt.find({x, y});
        return it == cnt.end() ? 0 : it->second;
    }
    int64_t count(int qx, int qy) const {
        int64_t total = 0;
        auto it = col.find(qx);
        if (it == col.end()) return 0;
        for (auto [y, c] : it->second) {
            int d = y - qy;
            if (d == 0) continue;
            for (int x : {qx + d, qx - d}) {
                total += c * get(x, qy) * get(x, y);
            }
        }
        return total;
    }
};

TEST(example) {
    Trace t("DetectSquares");
    DetectSquares ds;
    CALL(t, ds, add, P{1, 1});
    CALL(t, ds, add, P{1, 4});
    CALL(t, ds, add, P{4, 1});
    EXPECT_CALL(t, 1, ds, count, P{4, 4});
    EXPECT_CALL(t, 0, ds, count, P{2, 2});
    CALL(t, ds, add, P{4, 1});
    EXPECT_CALL(t, 2, ds, count, P{4, 4});
    EXPECT_CALL(t, 0, ds, count, P{1, 4});
}

TEST(duplicates_and_shapes) {
    {
        Trace t("DetectSquares");
        DetectSquares ds;
        for (P p : {P{0, 0}, P{0, 2}, P{0, 0}, P{0, 2}, P{2, 0}, P{0, 2}}) {
            CALL(t, ds, add, p);
        }
        EXPECT_CALL(t, 6, ds, count, P{2, 2});
        EXPECT_CALL(t, 0, ds, count, P{2, 0});
        CALL(t, ds, add, P{2, 2});
        EXPECT_CALL(t, 6, ds, count, P{2, 0});
    }
    {
        Trace t("DetectSquares");
        DetectSquares ds;
        CALL(t, ds, add, P{0, 0});
        CALL(t, ds, add, P{0, 2});
        CALL(t, ds, add, P{3, 0});
        EXPECT_CALL(t, 0, ds, count, P{3, 2});
        for (int k = 0; k < 3; ++k) {
            CALL(t, ds, add, P{5, 5});
        }
        EXPECT_CALL(t, 0, ds, count, P{5, 5});
        CALL(t, ds, add, P{7, 5});
        CALL(t, ds, add, P{9, 5});
        EXPECT_CALL(t, 0, ds, count, P{8, 5});
        CALL(t, ds, add, P{5, 7});
        EXPECT_CALL(t, 3, ds, count, P{7, 7});
    }
    {
        Trace t("DetectSquares");
        DetectSquares ds;
        CALL(t, ds, add, P{0, 0});
        CALL(t, ds, add, P{0, 1000});
        CALL(t, ds, add, P{1000, 0});
        EXPECT_CALL(t, 1, ds, count, P{1000, 1000});
        EXPECT_CALL(t, 0, ds, count, P{0, 0});
        EXPECT_CALL(t, 0, ds, count, P{999, 999});
    }
}

TEST(all_four_directions) {
    Trace t("DetectSquares");
    DetectSquares ds;
    for (P p : {P{3, 5}, P{7, 5}, P{5, 3}, P{5, 7}, P{3, 3}, P{7, 3}, P{3, 7}, P{7, 7}, P{2, 5}, P{5, 2}, P{2, 2}}) {
        CALL(t, ds, add, p);
    }
    EXPECT_CALL(t, 5, ds, count, P{5, 5});
    EXPECT_CALL(t, 1, ds, count, P{3, 3});
    EXPECT_CALL(t, 1, ds, count, P{7, 7});
}

TEST(random_small) {
    Rng rng(2013);
    for (int run = 0; run < 20; ++run) {
        Trace t("DetectSquares");
        DetectSquares ds;
        vector<Pt> stored;
        int lim = rng(2, 4);
        for (int k = 0; k < 40; ++k) {
            Pt p = {rng(0, lim), rng(0, lim)};
            if (stored.size() < 18 && rng.coin(0.55)) {
                stored.push_back(p);
                CALL(t, ds, add, P{p.first, p.second});
            } else {
                EXPECT_CALL(t, brute_count(stored, p), ds, count, P{p.first, p.second});
            }
        }
    }
}

TEST(large) {
    Rng rng(20130);
    const vector<int> coords = {0, 1, 2, 3, 4, 996, 997, 998, 999, 1000};
    SideOracle oracle;
    Trace t("DetectSquares");
    DetectSquares ds;
    for (int i = 0; i < 3000; ++i) {
        int x = rng.pick(coords), y = rng.pick(coords);
        if (i < 600 || rng.coin()) {
            oracle.add(x, y);
            CALL(t, ds, add, P{x, y});
        } else {
            EXPECT_CALL(t, static_cast<int>(oracle.count(x, y)), ds, count, P{x, y});
        }
    }
}

}
