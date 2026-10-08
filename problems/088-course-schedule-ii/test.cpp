#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Edges = vector<vector<int>>;

static void run(int n, const Edges& pre, bool possible) {
    Edges arg = pre;
    vector<int> got = Solution().findOrder(n, arg);
    if (!possible) {
        check(got, {}, "numCourses", n, "prerequisites", pre);
        return;
    }
    vector<int> all(n);
    iota(all.begin(), all.end(), 0);
    ensure(sorted(got) == all, "the order must contain every course 0..numCourses-1 exactly once", "got", got,
           "numCourses", n, "prereqs", pre);
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[got[i]] = i;
    }
    for (auto& p : pre) {
        if (pos[p[1]] > pos[p[0]]) {
            ensure(false, "course " + to_string(p[1]) + " must come before course " + to_string(p[0]), "got", got,
                   "numCourses", n, "prereqs", pre);
        }
    }
}

static bool possible(int n, const Edges& pre) {
    vector<vector<bool>> reach(n, vector<bool>(n));
    for (auto& p : pre) {
        reach[p[1]][p[0]] = true;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (reach[i][k] && reach[k][j]) {
                    reach[i][j] = true;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (reach[i][i]) return false;
    }
    return true;
}

TEST(examples) {
    run(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true);
    run(2, {{0, 1}, {1, 0}}, false);
    run(1, {}, true);
}

TEST(edge_cases) {
    run(2, {{1, 0}}, true);
    run(2, {{0, 1}}, true);
    run(3, {}, true);
    run(3, {{0, 1}, {1, 2}, {2, 0}}, false);
    run(5, {{1, 0}, {3, 2}, {4, 3}, {2, 4}}, false);
    run(6, {{1, 0}, {2, 1}, {4, 3}, {5, 4}}, true);
    run(5, {{4, 0}, {4, 1}, {4, 2}, {4, 3}}, true);
    run(5, {{1, 0}, {2, 0}, {3, 0}, {4, 0}}, true);
}

TEST(random) {
    Rng rng(88);
    for (int t = 0; t < 500; ++t) {
        int n = rng(1, 8), m = rng(0, n * 2);
        set<vector<int>> pairs;
        for (int i = 0; i < m; ++i) {
            int a = rng(0, n - 1), b = rng(0, n - 1);
            if (a != b) {
                pairs.insert({a, b});
            }
        }
        Edges pre(pairs.begin(), pairs.end());
        rng.shuffle(pre);
        run(n, pre, possible(n, pre));
    }
}

TEST(large) {
    const int n = 2000;
    Rng rng(880);
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    rng.shuffle(label);

    Edges chain;
    for (int i = 0; i + 1 < n; ++i) {
        chain.push_back({label[i + 1], label[i]});
    }
    rng.shuffle(chain);
    run(n, chain, true);
    chain.push_back({label[0], label[n - 1]});
    run(n, chain, false);

    Edges layered;
    for (int i = 0; i + 1 < n / 2; ++i) {
        for (int x : {0, 1}) {
            for (int y : {0, 1}) {
                layered.push_back({label[2 * (i + 1) + x], label[2 * i + y]});
            }
        }
    }
    rng.shuffle(layered);
    run(n, layered, true);

    set<pair<int, int>> pairs;
    for (int i = 0; i + 1 < n; ++i) {
        pairs.insert({i, i + 1});
    }
    while (pairs.size() < 50000) {
        int i = rng(0, n - 1), j = rng(0, n - 1);
        if (i != j) {
            pairs.insert({min(i, j), max(i, j)});
        }
    }
    Edges dense;
    for (auto [i, j] : pairs) {
        dense.push_back({label[j], label[i]});
    }
    rng.shuffle(dense);
    run(n, dense, true);
    dense.push_back({label[10], label[n - 10]});
    run(n, dense, false);
}

}
