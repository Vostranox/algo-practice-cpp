#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static vector<vector<int>> from_masks(const vector<int>& masks) {
    vector<vector<int>> out;
    for (int m : masks) {
        out.emplace_back();
        for (int i = 0; m >> i; ++i) {
            if (m >> i & 1) {
                out.back().push_back(i + 1);
            }
        }
    }
    return out;
}

static void run_masks(int n, int k, vector<int> want) {
    auto got = Solution().combine(n, k);
    vector<int> masks;
    for (auto& comb : got) {
        int mask = 0;
        bool ok = static_cast<int>(comb.size()) == k;
        for (int x : comb) {
            ok &= x >= 1 && x <= n && !(mask >> (x - 1) & 1);
            if (ok) {
                mask |= 1 << (x - 1);
            }
        }
        if (!ok) {
            ensure(false, "every combination must consist of k = " + to_string(k) + " different numbers from 1 to " +
                              to_string(n) + ", but got " + repr(comb), "n", n, "k", k);
        }
        masks.push_back(mask);
    }
    sort(masks.begin(), masks.end());
    if (auto d = adjacent_find(masks.begin(), masks.end()); d != masks.end()) {
        ensure(false, "the combination " + repr(from_masks({*d})[0]) + " appears more than once", "n", n, "k", k);
    }
    sort(want.begin(), want.end());
    if (masks != want) {
        check(sort_all(got), sort_all(from_masks(want)), "n", n, "k", k);
    }
}

static void run(int n, int k, const vector<vector<int>>& want) {
    vector<int> masks;
    for (auto& comb : want) {
        int mask = 0;
        for (int x : comb) {
            mask |= 1 << (x - 1);
        }
        masks.push_back(mask);
    }
    run_masks(n, k, masks);
}

static vector<int> oracle(int n, int k) {
    vector<int> out;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) == k) {
            out.push_back(mask);
        }
    }
    return out;
}

TEST(examples) {
    run(4, 2, {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}});
    run(3, 3, {{1, 2, 3}});
    run(5, 1, {{1}, {2}, {3}, {4}, {5}});
}

TEST(edge_cases) {
    run(1, 1, {{1}});
    run(2, 1, {{1}, {2}});
    run(2, 2, {{1, 2}});
    run(4, 3, {{1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}});
    run(5, 4, {{1, 2, 3, 4}, {1, 2, 3, 5}, {1, 2, 4, 5}, {1, 3, 4, 5}, {2, 3, 4, 5}});
    run(20, 20, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}});
}

TEST(all_small) {
    for (int n = 1; n <= 12; ++n) {
        for (int k = 1; k <= n; ++k) {
            run_masks(n, k, oracle(n, k));
        }
    }
}

TEST(large) {
    for (auto [n, k] : vector<pair<int, int>>{{20, 10}, {20, 1}, {20, 19}, {19, 9}, {18, 6}, {17, 14}}) {
        run_masks(n, k, oracle(n, k));
    }
}

}
