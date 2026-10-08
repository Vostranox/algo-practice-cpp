#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Edges = vector<vector<int>>;

static void run(const Edges& edges, const vector<int>& want) {
    Edges arg = edges;
    check(Solution().findRedundantConnection(arg), want, "edges", edges);
}

static bool connected(int n, const Edges& edges) {
    vector<vector<int>> g(n + 1);
    for (auto& e : edges) {
        g[e[0]].push_back(e[1]), g[e[1]].push_back(e[0]);
    }
    vector<bool> seen(n + 1);
    vector<int> stack{1};
    seen[1] = true;
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

static vector<int> redundant(const Edges& edges) {
    int n = edges.size();
    for (int i = n - 1; i >= 0; --i) {
        Edges rest = edges;
        rest.erase(rest.begin() + i);
        if (connected(n, rest)) return edges[i];
    }
    return {};
}

struct Case {
    Edges edges;
    vector<int> want;
};

static Case random_case(Rng& rng, int n) {
    vector<int> order(n), parent(n + 1, 0), depth(n + 1, 0);
    iota(order.begin(), order.end(), 1);
    rng.shuffle(order);
    set<pair<int, int>> es;
    for (int i = 1; i < n; ++i) {
        int v = order[i], p = order[rng(0, i - 1)];
        parent[v] = p, depth[v] = depth[p] + 1;
        es.insert({min(v, p), max(v, p)});
    }
    int a, b;
    do {
        a = rng(1, n), b = rng(1, n);
    } while (a == b || es.count({min(a, b), max(a, b)}));
    es.insert({min(a, b), max(a, b)});
    set<pair<int, int>> cycle{{min(a, b), max(a, b)}};
    for (int x = a, y = b; x != y;) {
        if (depth[x] < depth[y]) {
            swap(x, y);
        }
        cycle.insert({min(x, parent[x]), max(x, parent[x])});
        x = parent[x];
    }
    Case c;
    for (auto [p, q] : es) {
        c.edges.push_back({p, q});
    }
    rng.shuffle(c.edges);
    for (auto& e : c.edges) {
        if (cycle.count({e[0], e[1]})) {
            c.want = e;
        }
    }
    return c;
}

TEST(examples) {
    run({{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}, {1, 4});
    run({{2, 3}, {1, 3}, {1, 2}, {3, 4}}, {1, 2});
    run({{1, 4}, {3, 4}, {1, 3}, {1, 2}, {4, 5}}, {1, 3});
}

TEST(edge_cases) {
    run({{1, 2}, {2, 3}, {1, 3}}, {1, 3});
    run({{1, 3}, {2, 3}, {1, 2}}, {1, 2});
    run({{1, 2}, {1, 3}, {2, 3}, {2, 4}, {4, 5}}, {2, 3});
    run({{3, 4}, {1, 2}, {2, 4}, {1, 5}, {1, 3}, {5, 6}}, {1, 3});
    run({{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}}, {1, 5});
    run({{4, 5}, {1, 5}, {1, 2}, {2, 3}, {3, 4}}, {3, 4});
}

TEST(random) {
    Rng rng(89);
    for (int t = 0; t < 300; ++t) {
        Edges edges = random_case(rng, rng(3, 12)).edges;
        run(edges, redundant(edges));
    }
}

TEST(large) {
    Rng rng(890);
    Edges ring;
    for (int i = 1; i < 1000; ++i) {
        ring.push_back({i, i + 1});
    }
    ring.push_back({1, 1000});
    rng.shuffle(ring);
    run(ring, ring.back());
    for (int t = 0; t < 50; ++t) {
        Case c = random_case(rng, 1000);
        run(c.edges, c.want);
    }
}

}
