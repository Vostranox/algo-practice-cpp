#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Adj = vector<vector<int>>;

static void run(const Adj& adj) {
    GraphNode* original = build_graph(adj);
    auto nodes = graph_nodes(original);
    unordered_set<GraphNode*> originals(nodes.begin(), nodes.end());
    GraphNode* got = Solution().cloneGraph(original);
    if (adj.empty()) {
        check(got, nullptr, "adj", adj);
        return;
    }
    ensure(got != nullptr, "returned nullptr; should return the copy of the node you were given", "adj", adj);
    ensure(got != original, "returned the original node instead of a copy", "adj", adj);
    vector<int> reused;
    for (GraphNode* n : graph_nodes(got)) {
        if (originals.count(n)) {
            reused.push_back(n->val);
        }
    }
    ensure(reused.empty(), "the copy contains original nodes instead of new ones", "reused",
           sorted(reused), "adj", adj);
    ensure(got->val == original->val, "should return the copy of the given node (value 1)", "got", got, "adj", adj);
    check(graph_to_adj(got), adj, "adj", adj);
    ensure(graph_to_adj(original) == adj, "the original graph was modified", "original now",
           graph_to_adj(original), "adj", adj);
}

static Adj random_connected(Rng& rng, int n, int extra) {
    set<pair<int, int>> edges;
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    rng.shuffle(order);
    for (int i = 1; i < n; ++i) {
        int a = order[i], b = order[rng(0, i - 1)];
        edges.insert({min(a, b), max(a, b)});
    }
    for (int i = 0; i < extra; ++i) {
        int a = rng(1, n), b = rng(1, n);
        if (a != b) {
            edges.insert({min(a, b), max(a, b)});
        }
    }
    Adj adj(n);
    for (auto [a, b] : edges) {
        adj[a - 1].push_back(b);
        adj[b - 1].push_back(a);
    }
    for (auto& nb : adj) {
        rng.shuffle(nb);
    }
    return adj;
}

TEST(examples) {
    run({{2, 3}, {1, 3}, {1, 2}});
    run({{2}, {1, 3}, {2, 4}, {3}});
    run({{}});
}

TEST(edge_cases) {
    run({{}});
    run({{2}, {1}});
    run({{3, 2}, {1}, {1}});
    run({{2, 3, 4, 5}, {1}, {1}, {1}, {1}});
    run({{2, 4}, {1, 3}, {2, 4}, {3, 1}});
    run({{2, 3, 4, 5}, {1, 3, 4, 5}, {1, 2, 4, 5}, {1, 2, 3, 5}, {1, 2, 3, 4}});
    run({});
}

TEST(random) {
    Rng rng(81);
    for (int t = 0; t < 100; ++t) {
        int n = rng(2, 100);
        run(random_connected(rng, n, rng(0, 2 * n)));
    }
    Adj path(100);
    for (int v = 1; v <= 100; ++v) {
        for (int u : {v - 1, v + 1}) {
            if (u >= 1 && u <= 100) {
                path[v - 1].push_back(u);
            }
        }
    }
    run(path);
    Adj full(100);
    for (int v = 1; v <= 100; ++v) {
        for (int u = 1; u <= 100; ++u) {
            if (u != v) {
                full[v - 1].push_back(u);
            }
        }
    }
    run(full);
}

}
