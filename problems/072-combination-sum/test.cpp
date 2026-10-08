#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> candidates, int target, vector<vector<int>> want) {
    vector<int> arg = candidates;
    auto got = sort_all(Solution().combinationSum(arg, target));
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the combination " + repr(*d) + " appears more than once",
               "candidates", candidates, "target", target, "got", got);
    }
    check(got, sort_all(want), "candidates", candidates, "target", target);
}

static vector<vector<int>> oracle(const vector<int>& c, int target) {
    vector<vector<int>> out;
    vector<int> count(c.size(), 0);
    while (true) {
        int64_t sum = 0;
        for (size_t i = 0; i < c.size(); ++i) {
            sum += static_cast<int64_t>(count[i]) * c[i];
        }
        if (sum == target) {
            out.emplace_back();
            for (size_t i = 0; i < c.size(); ++i) {
                out.back().insert(out.back().end(), count[i], c[i]);
            }
        }
        size_t i = 0;
        while (i < c.size() && count[i] == target / c[i]) {
            count[i++] = 0;
        }
        if (i == c.size()) return out;
        ++count[i];
    }
}

TEST(examples) {
    run({3, 4, 5}, 8, {{3, 5}, {4, 4}});
    run({2, 7}, 11, {{2, 2, 7}});
    run({6, 9}, 5, {});
}

TEST(edge_cases) {
    run({2}, 1, {});
    run({2}, 40, {vector<int>(20, 2)});
    run({40}, 40, {{40}});
    run({3, 5}, 4, {});
    run({7, 3, 2}, 7, {{7}, {2, 2, 3}});
    run({2, 3, 4}, 8, {{2, 2, 2, 2}, {2, 3, 3}, {2, 2, 4}, {4, 4}});
    vector<int> big;
    for (int v = 40; v >= 11; --v) {
        big.push_back(v);
    }
    run(big, 40, {{40}, {11, 29}, {12, 28}, {13, 27}, {14, 26}, {15, 25}, {16, 24}, {17, 23}, {18, 22},
                  {19, 21}, {20, 20}, {11, 11, 18}, {11, 12, 17}, {11, 13, 16}, {11, 14, 15},
                  {12, 12, 16}, {12, 13, 15}, {12, 14, 14}, {13, 13, 14}});
}

TEST(random) {
    Rng rng(39);
    for (int done = 0; done < 500;) {
        vector<int> pool(14);
        iota(pool.begin(), pool.end(), 2);
        rng.shuffle(pool);
        pool.resize(rng(1, 5));
        int target = rng(1, 25);
        auto want = oracle(pool, target);
        if (want.size() >= 150) continue;
        run(pool, target, want);
        ++done;
    }
}

}
