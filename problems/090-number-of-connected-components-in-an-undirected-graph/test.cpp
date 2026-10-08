#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Edges = vector<vector<int>>;

static void run(int n, const Edges& edges, int want) {
    Edges arg = edges;
    check(Solution().countComponents(n, arg), want, "n", n, "edges", edges);
}

static int components(int n, const Edges& edges) {
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    for (bool changed = true; changed;) {
        changed = false;
        for (auto& e : edges) {
            int m = min(label[e[0]], label[e[1]]);
            if (label[e[0]] != m || label[e[1]] != m) {
                label[e[0]] = label[e[1]] = m, changed = true;
            }
        }
    }
    return set<int>(label.begin(), label.end()).size();
}

TEST(examples) {
    run(6, {{0, 1}, {2, 3}, {1, 4}}, 3);
    run(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, 1);
    run(3, {}, 3);
}

TEST(edge_cases) {
    run(1, {}, 1);
    run(2, {{0, 1}}, 1);
    run(2, {{1, 0}}, 1);
    run(5, {{0, 1}, {1, 2}, {0, 2}}, 3);
    run(4, {{2, 3}}, 3);
    run(6, {{5, 0}, {4, 1}, {3, 2}}, 3);
    run(5, {{0, 4}, {1, 3}, {3, 4}, {2, 1}}, 1);
}

TEST(random) {
    Rng rng(90);
    for (int t = 0; t < 500; ++t) {
        int n = rng(1, 12), m = rng(0, n + 2);
        set<pair<int, int>> es;
        for (int i = 0; i < m && n > 1; ++i) {
            int a = rng(0, n - 1), b = rng(0, n - 1);
            if (a != b) {
                es.insert({min(a, b), max(a, b)});
            }
        }
        Edges edges;
        for (auto [a, b] : es) {
            edges.push_back(rng.coin() ? vector<int>{a, b} : vector<int>{b, a});
        }
        rng.shuffle(edges);
        run(n, edges, components(n, edges));
    }
}

TEST(large) {
    const int n = 2000;
    Rng rng(900);
    Edges path;
    for (int i = 0; i + 1 < n; ++i) {
        path.push_back({i, i + 1});
    }
    rng.shuffle(path);
    run(n, path, 1);
    run(n, {}, n);
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    rng.shuffle(label);
    vector<int> cuts{0, 1700};
    for (int i = 0; i < 36; ++i) {
        int c;
        do {
            c = rng(1, 1699);
        } while (find(cuts.begin(), cuts.end(), c) != cuts.end());
        cuts.push_back(c);
    }
    sort(cuts.begin(), cuts.end());
    set<pair<int, int>> es;
    auto add = [&](int a, int b) { es.insert({min(label[a], label[b]), max(label[a], label[b])}); };
    for (size_t g = 0; g + 1 < cuts.size(); ++g) {
        for (int i = cuts[g] + 1; i < cuts[g + 1]; ++i) {
            add(i, rng(cuts[g], i - 1));
        }
    }
    while (es.size() < 5000) {
        size_t g = rng(0, cuts.size() - 2);
        int lo = cuts[g], hi = cuts[g + 1] - 1, a = rng(lo, hi), b = rng(lo, hi);
        if (a != b) {
            add(a, b);
        }
    }
    Edges edges;
    for (auto [a, b] : es) {
        edges.push_back({a, b});
    }
    rng.shuffle(edges);
    run(n, edges, 37 + 300);
}

}
