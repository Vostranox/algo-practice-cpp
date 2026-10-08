#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> candidates, int target, vector<vector<int>> want) {
    vector<int> arg = candidates;
    auto got = sort_all(Solution().combinationSum2(arg, target));
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the combination " + repr(*d) + " appears more than once",
               "candidates", candidates, "target", target, "got", got);
    }
    check(got, sort_all(want), "candidates", candidates, "target", target);
}

static vector<vector<int>> oracle(const vector<int>& c, int target) {
    set<vector<int>> found;
    for (int mask = 1; mask < (1 << c.size()); ++mask) {
        int sum = 0;
        for (size_t i = 0; i < c.size(); ++i) {
            if (mask >> i & 1) {
                sum += c[i];
            }
        }
        if (sum != target) continue;
        vector<int> pick;
        for (size_t i = 0; i < c.size(); ++i) {
            if (mask >> i & 1) {
                pick.push_back(c[i]);
            }
        }
        found.insert(sorted(pick));
    }
    return vector<vector<int>>(found.begin(), found.end());
}

static void partitions(int n, int largest, vector<int>& cur, vector<vector<int>>& out) {
    if (n == 0) {
        out.push_back(cur);
        return;
    }
    for (int p = min(n, largest); p >= 1; --p) {
        cur.push_back(p);
        partitions(n - p, p, cur, out);
        cur.pop_back();
    }
}

TEST(examples) {
    run({4, 1, 3, 1, 2, 5}, 6, {{1, 5}, {2, 4}, {1, 1, 4}, {1, 2, 3}});
    run({3, 3, 3}, 6, {{3, 3}});
    run({5, 7}, 3, {});
}

TEST(edge_cases) {
    run({1}, 1, {{1}});
    run({2}, 1, {});
    run({50, 30, 1}, 30, {{30}});
    run({2, 2, 2, 3, 3}, 7, {{2, 2, 3}});
    run({4, 4}, 4, {{4}});
    run({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10,
        {{10}, {1, 9}, {2, 8}, {3, 7}, {4, 6}, {1, 2, 7}, {1, 3, 6}, {1, 4, 5}, {2, 3, 5}, {1, 2, 3, 4}});
}

TEST(random) {
    Rng rng(40);
    for (int iter = 0; iter < 300; ++iter) {
        int hi = rng.pick(vector<int>{4, 10, 50});
        vector<int> candidates = rng.ints(rng(1, 12), 1, hi);
        int target = rng(1, 30);
        run(candidates, target, oracle(candidates, target));
    }
}

TEST(large) {
    run(vector<int>(100, 1), 30, {vector<int>(30, 1)});
    Rng rng(400);
    vector<int> cands(50, 1);
    cands.insert(cands.end(), 50, 2);
    rng.shuffle(cands);
    vector<vector<int>> want;
    for (int b = 0; b <= 15; ++b) {
        want.push_back(vector<int>(30 - 2 * b, 1));
        want.back().insert(want.back().end(), b, 2);
    }
    run(cands, 30, want);
    cands.clear();
    for (int rep = 0; rep < 2; ++rep) {
        for (int v = 1; v <= 50; ++v) {
            cands.push_back(v);
        }
    }
    rng.shuffle(cands);
    vector<vector<int>> all;
    vector<int> cur;
    partitions(30, 30, cur, all);
    want.clear();
    for (auto& p : all) {
        bool ok = true;
        for (size_t i = 0; i + 2 < p.size(); ++i) {
            ok &= !(p[i] == p[i + 2]);
        }
        if (ok) {
            want.push_back(p);
        }
    }
    run(cands, 30, want);
}

}
