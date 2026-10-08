#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Edges = vector<vector<int>>;

static void run(int n, const Edges& pre, bool want) {
    Edges arg = pre;
    check(Solution().canFinish(n, arg), want, "numCourses", n, "prerequisites", pre);
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
    run(3, {{1, 0}, {2, 1}}, true);
    run(3, {{1, 0}, {2, 1}, {0, 2}}, false);
    run(2, {}, true);
}

TEST(edge_cases) {
    run(1, {}, true);
    run(1, {{0, 0}}, false);
    run(2, {{1, 0}, {0, 1}}, false);
    run(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true);
    run(5, {{1, 0}, {3, 2}, {4, 3}, {2, 4}}, false);
    run(4, {{1, 0}, {2, 0}, {3, 0}}, true);
    run(6, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}}, true);
    run(4, {{1, 0}, {2, 1}, {3, 2}, {1, 3}}, false);
}

TEST(random) {
    Rng rng(87);
    for (int t = 0; t < 500; ++t) {
        int n = rng(1, 8), m = rng(0, n * 2);
        set<vector<int>> pairs;
        for (int i = 0; i < m; ++i) {
            int a = rng(0, n - 1), b = rng(0, n - 1);
            if (a != b || rng.coin(0.05)) {
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
    Rng rng(870);
    Edges chain;
    for (int i = 0; i + 1 < n; ++i) {
        chain.push_back({i + 1, i});
    }
    run(n, chain, true);
    chain.push_back({0, n - 1});
    run(n, chain, false);

    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    rng.shuffle(label);
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
    layered.push_back({label[0], label[n - 1]});
    run(n, layered, false);

    set<pair<int, int>> pairs;
    for (int i = 0; i + 1 < n; ++i) {
        pairs.insert({i, i + 1});
    }
    while (pairs.size() < 4999) {
        int i = rng(0, n - 1), j = rng(0, n - 1);
        if (i != j) {
            pairs.insert({min(i, j), max(i, j)});
        }
    }
    Edges dag;
    for (auto [i, j] : pairs) {
        dag.push_back({label[j], label[i]});
    }
    rng.shuffle(dag);
    run(n, dag, true);
    dag.push_back({label[n / 3], label[2 * n / 3]});
    run(n, dag, false);
}

}
