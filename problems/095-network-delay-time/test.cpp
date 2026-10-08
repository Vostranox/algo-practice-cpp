#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Links = vector<vector<int>>;

static void run(const Links& times, int n, int k, int want) {
    Links arg = times;
    check(Solution().networkDelayTime(arg, n, k), want, "times", times, "n", n, "k", k);
}

static int delay(const Links& times, int n, int k) {
    const int64_t INF = INT64_MAX / 4;
    vector<int64_t> dist(n + 1, INF);
    dist[k] = 0;
    for (int round = 1; round < n; ++round) {
        for (auto& t : times) {
            if (dist[t[0]] < INF) {
                dist[t[1]] = min(dist[t[1]], dist[t[0]] + t[2]);
            }
        }
    }
    int64_t worst = *max_element(dist.begin() + 1, dist.end());
    return worst >= INF ? -1 : static_cast<int>(worst);
}

static pair<Links, int> planted(Rng& rng, int n, int k, int m) {
    vector<int> order{k}, d(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (v != k) {
            order.push_back(v);
        }
    }
    for (int i = n - 1; i > 1; --i) {
        swap(order[i], order[rng(1, i)]);
    }
    map<pair<int, int>, int> links;
    for (int i = 1; i < n; ++i) {
        int v = order[i], p = order[rng(0, i - 1)];
        d[v] = d[p] + rng(0, 20);
        links[{p, v}] = d[v] - d[p];
    }
    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (u != v && !links.count({u, v}) && d[v] - d[u] <= 100) {
                candidates.push_back({u, v});
            }
        }
    }
    rng.shuffle(candidates);
    for (size_t i = 0; i < candidates.size() && static_cast<int>(links.size()) < m; ++i) {
        auto [u, v] = candidates[i];
        links[{u, v}] = rng(max(0, d[v] - d[u]), 100);
    }
    Links times;
    for (auto& [uv, w] : links) {
        times.push_back({uv.first, uv.second, w});
    }
    rng.shuffle(times);
    return {times, *max_element(d.begin() + 1, d.end())};
}

TEST(examples) {
    run({{1, 2, 4}, {1, 3, 1}, {3, 2, 2}, {2, 4, 1}}, 4, 1, 4);
    run({{1, 2, 5}}, 3, 1, -1);
    run({{1, 2, 0}, {2, 3, 0}}, 3, 1, 0);
}

TEST(edge_cases) {
    run({{2, 1, 3}}, 2, 2, 3);
    run({{2, 1, 3}}, 2, 1, -1);
    run({{2, 1, 3}, {2, 3, 7}, {1, 3, 2}}, 3, 2, 5);
    run({{1, 2, 1}, {2, 1, 1}}, 2, 1, 1);
    run({{1, 2, 100}, {2, 3, 100}, {3, 4, 100}}, 4, 1, 300);
    run({{1, 2, 1}, {1, 3, 1}, {1, 4, 1}, {1, 5, 1}}, 5, 1, 1);
    run({{3, 1, 5}, {3, 2, 5}, {1, 2, 0}, {2, 1, 0}}, 3, 3, 5);
}

TEST(random) {
    Rng rng(95);
    for (int t = 0; t < 500; ++t) {
        int n = rng(2, 8), k = rng(1, n);
        set<pair<int, int>> seen;
        Links times;
        for (int i = rng(1, n * (n - 1)); i > 0; --i) {
            int u = rng(1, n), v = rng(1, n);
            if (u != v && seen.insert({u, v}).second) {
                times.push_back({u, v, rng(0, rng.coin(0.2) ? 2 : 100)});
            }
        }
        run(times, n, k, delay(times, n, k));
    }
}

TEST(large) {
    Rng rng(950);
    for (int t = 0; t < 5; ++t) {
        int k = rng(1, 100);
        auto [times, want] = planted(rng, 100, k, 6000);
        run(times, 100, k, want);
        int cut = k % 100 + 1;
        Links rest;
        for (auto& l : times) {
            if (l[1] != cut) {
                rest.push_back(l);
            }
        }
        run(rest, 100, k, -1);
    }
    Links times;
    for (int i = 1; i <= 100; ++i) {
        for (int j = i + 1; j <= 100; ++j) {
            times.push_back({i, j, j == i + 1 ? 1 : j - i + 1});
        }
    }
    rng.shuffle(times);
    run(times, 100, 1, 99);
    run(times, 100, 50, -1);
}

}
