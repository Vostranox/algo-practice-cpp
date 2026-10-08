#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Edges = vector<vector<int>>;

static void run(int n, const Edges& edges, bool want) {
    Edges arg = edges;
    check(Solution().validTree(n, arg), want, "n", n, "edges", edges);
}

static bool is_tree(int n, const Edges& edges) {
    if (static_cast<int>(edges.size()) != n - 1) return false;
    vector<vector<int>> g(n);
    for (auto& e : edges) {
        g[e[0]].push_back(e[1]), g[e[1]].push_back(e[0]);
    }
    vector<bool> seen(n);
    vector<int> stack{0};
    seen[0] = true;
    int count = 1;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        for (int v : g[u]) {
            if (!seen[v]) {
                seen[v] = true, ++count, stack.push_back(v);
            }
        }
    }
    return count == n;
}

static Edges random_tree(Rng& rng, int n) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    rng.shuffle(order);
    Edges edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({order[i], order[rng(0, i - 1)]});
    }
    rng.shuffle(edges);
    return edges;
}

TEST(examples) {
    run(5, {{0, 1}, {0, 2}, {2, 3}, {2, 4}}, true);
    run(4, {{0, 1}, {1, 2}, {2, 3}, {1, 3}}, false);
    run(4, {{0, 1}, {2, 3}}, false);
}

TEST(edge_cases) {
    run(1, {}, true);
    run(2, {}, false);
    run(2, {{1, 0}}, true);
    run(4, {{0, 1}, {1, 2}, {2, 0}}, false);
    run(3, {{0, 1}, {1, 2}, {0, 2}}, false);
    run(5, {{0, 1}, {0, 2}, {0, 3}, {0, 4}}, true);
    run(5, {{4, 3}, {3, 2}, {2, 1}, {1, 0}}, true);
    run(6, {{0, 1}, {1, 2}, {3, 4}, {4, 5}, {5, 3}}, false);
}

TEST(random) {
    Rng rng(91);
    for (int t = 0; t < 500; ++t) {
        int n = rng(1, 9);
        Edges edges;
        if (rng.coin()) {
            edges = random_tree(rng, n);
            if (!edges.empty() && rng.coin(0.3)) {
                edges.erase(edges.begin() + rng(0, edges.size() - 1));
            }
        } else {
            set<pair<int, int>> es;
            for (int i = rng(0, n + 1); i > 0 && n > 1; --i) {
                int a = rng(0, n - 1), b = rng(0, n - 1);
                if (a != b) {
                    es.insert({min(a, b), max(a, b)});
                }
            }
            for (auto [a, b] : es) {
                edges.push_back({a, b});
            }
        }
        if (n > 2 && rng.coin(0.2)) {
            set<pair<int, int>> have;
            for (auto& e : edges) {
                have.insert({min(e[0], e[1]), max(e[0], e[1])});
            }
            int a = rng(0, n - 1), b = rng(0, n - 1);
            if (a != b && !have.count({min(a, b), max(a, b)})) {
                edges.push_back({a, b});
            }
        }
        rng.shuffle(edges);
        run(n, edges, is_tree(n, edges));
    }
}

TEST(large) {
    const int n = 2000;
    Rng rng(910);
    Edges tree = random_tree(rng, n);
    run(n, tree, true);
    Edges cut = tree;
    cut.pop_back();
    run(n, cut, false);
    Edges extra = tree;
    set<pair<int, int>> have;
    for (auto& e : tree) {
        have.insert({min(e[0], e[1]), max(e[0], e[1])});
    }
    int a, b;
    do {
        a = rng(0, n - 1), b = rng(0, n - 1);
    } while (a == b || have.count({min(a, b), max(a, b)}));
    extra.push_back({a, b});
    run(n, extra, false);
    Edges path;
    for (int i = 0; i + 1 < n; ++i) {
        path.push_back({i, i + 1});
    }
    run(n, path, true);
    Edges loop;
    for (int i = 0; i + 1 < n - 1; ++i) {
        loop.push_back({i, i + 1});
    }
    loop.push_back({0, n - 2});
    run(n, loop, false);
}

}
