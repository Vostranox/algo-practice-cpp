#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Flights = vector<vector<int>>;

static void run(int n, const Flights& flights, int src, int dst, int k, int want) {
    Flights arg = flights;
    check(Solution().findCheapestPrice(n, arg, src, dst, k), want, "n", n, "flights", flights, "src", src, "dst",
          dst, "k", k);
}

static void walk(const vector<vector<pair<int, int>>>& out, int u, int dst, int64_t cost, int left, int64_t& best) {
    if (u == dst) {
        if (best < 0 || cost < best) {
            best = cost;
        }
        return;
    }
    if (left == 0) return;
    for (auto [v, p] : out[u]) {
        walk(out, v, dst, cost + p, left - 1, best);
    }
}

static int cheapest(int n, const Flights& flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> out(n);
    for (auto& f : flights) {
        out[f[0]].push_back({f[1], f[2]});
    }
    int64_t best = -1;
    walk(out, src, dst, 0, k + 1, best);
    return best;
}

TEST(examples) {
    Flights f{{0, 1, 100}, {1, 2, 100}, {2, 3, 100}, {0, 2, 500}, {1, 3, 600}};
    run(4, f, 0, 3, 1, 600);
    run(4, f, 0, 3, 2, 300);
    run(3, {{0, 1, 50}}, 0, 2, 1, -1);
}

TEST(edge_cases) {
    run(3, {{0, 1, 5}, {1, 2, 5}, {0, 2, 100}}, 0, 2, 0, 100);
    run(3, {{0, 1, 5}, {1, 2, 5}, {0, 2, 100}}, 0, 2, 1, 10);
    run(4, {{0, 1, 1}, {1, 2, 1}, {0, 2, 5}, {2, 3, 1}}, 0, 3, 1, 6);
    run(4, {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 100}}, 0, 3, 0, 100);
    run(4, {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 100}}, 0, 3, 1, 100);
    run(4, {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 100}}, 0, 3, 2, 3);
    run(2, {}, 0, 1, 0, -1);
    run(2, {{1, 0, 5}}, 0, 1, 1, -1);
    run(4, {{0, 1, 1}, {1, 2, 1}, {2, 0, 1}, {2, 3, 10}}, 0, 3, 3, 12);
    run(4, {{0, 1, 1}, {1, 2, 1}, {2, 0, 1}, {2, 3, 10}}, 0, 3, 1, -1);
}

TEST(random) {
    Rng rng(98);
    for (int t = 0; t < 500; ++t) {
        int n = rng(2, 6), top = rng.coin() ? 20 : 10000;
        Flights flights;
        double p = rng.real();
        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                if (rng.coin(p)) {
                    if (rng.coin()) {
                        flights.push_back({a, b, rng(1, top)});
                    } else {
                        flights.push_back({b, a, rng(1, top)});
                    }
                }
            }
        }
        rng.shuffle(flights);
        int src = rng(0, n - 1), dst = rng(0, n - 2);
        if (dst >= src) {
            ++dst;
        }
        int k = rng(0, n - 1);
        run(n, flights, src, dst, k, cheapest(n, flights, src, dst, k));
    }
}

TEST(large) {
    Rng rng(980);
    Flights flights;
    for (int i = 0; i < 100; ++i) {
        for (int j = i + 1; j < 100; ++j) {
            flights.push_back({i, j, (j - i) * (j - i)});
        }
    }
    rng.shuffle(flights);
    auto best = [](int L, int k) {
        int m = min(k + 1, L), q = L / m, r = L % m;
        return r * (q + 1) * (q + 1) + (m - r) * q * q;
    };
    for (int k : {0, 1, 4, 30, 99}) {
        run(100, flights, 0, 99, k, best(99, k));
    }
    run(100, flights, 20, 80, 7, best(60, 7));
    run(100, flights, 50, 10, 10, -1);
}

}
