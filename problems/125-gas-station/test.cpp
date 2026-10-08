#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> gas, vector<int> cost, int want) {
    vector<int> g = gas, c = cost;
    check(Solution().canCompleteCircuit(g, c), want, "gas", gas, "cost", cost);
}

static vector<int> valid_starts(const vector<int>& gas, const vector<int>& cost) {
    int n = static_cast<int>(gas.size());
    vector<int> out;
    for (int s = 0; s < n; ++s) {
        int tank = 0;
        bool ok = true;
        for (int k = 0; k < n && ok; ++k) {
            int i = (s + k) % n;
            tank += gas[i] - cost[i];
            ok = tank >= 0;
        }
        if (ok) {
            out.push_back(s);
        }
    }
    return out;
}

TEST(examples) {
    run({2, 3, 4}, {3, 4, 1}, 2);
    run({1, 2, 3}, {2, 3, 2}, -1);
    run({5}, {4}, 0);
}

TEST(edge_cases) {
    run({3}, {3}, 0);
    run({2}, {3}, -1);
    run({0}, {0}, 0);
    run({1, 0}, {0, 1}, 0);
    run({0, 1}, {1, 0}, 1);
    run({0, 0, 5}, {1, 1, 3}, 2);
    run({4, 0, 0, 4}, {1, 4, 2, 1}, 3);
    run({2, 2, 3}, {2, 3, 2}, 2);
    run({3, 3, 3}, {4, 4, 1}, 2);
    run({10000, 0}, {0, 10000}, 0);
    run({5, 5, 5, 5}, {6, 6, 6, 1}, 3);
    run({1, 2, 3, 4}, {2, 3, 4, 2}, -1);
}

TEST(random) {
    Rng rng(134);
    for (int done = 0; done < 600;) {
        int n = rng(1, 7);
        vector<int> gas = rng.ints(n, 0, 5), cost = rng.ints(n, 0, 5);
        vector<int> starts = valid_starts(gas, cost);
        if (starts.size() > 1) continue;
        run(gas, cost, starts.empty() ? -1 : starts[0]);
        ++done;
    }
}

static void build(Rng& rng, int n, int total, bool flat, vector<int>& gas, vector<int>& cost) {
    vector<int> P = {0};
    int cur = total + 1;
    for (int i = 1; i < n; ++i) {
        if (flat) {
            if (rng.coin(0.05) && cur < total + 9000) {
                ++cur;
            }
            P.push_back(cur);
        } else {
            P.push_back(total + rng(1, 5000));
        }
    }
    P.push_back(total);
    gas.assign(n, 0);
    cost.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        int d = P[i + 1] - P[i];
        cost[i] = rng(max(0, -d), min(10000, 10000 - d));
        gas[i] = cost[i] + d;
    }
}

static vector<int> rotated(const vector<int>& v, int r) {
    vector<int> out(v.begin() + r, v.end());
    out.insert(out.end(), v.begin(), v.begin() + r);
    return out;
}

TEST(large) {
    const int n = 100000;
    Rng rng(7);
    vector<int> gas, cost;
    for (auto [total, flat, r] : vector<tuple<int, bool, int>>{{0, true, 3}, {2500, true, 60000}, {17, false, 99999}}) {
        build(rng, n, total, flat, gas, cost);
        run(rotated(gas, r), rotated(cost, r), (n - r) % n);
    }
    build(rng, n, 0, true, gas, cost);
    for (int i = 0;; ++i) {
        if (cost[i] < 10000) {
            ++cost[i];
            break;
        }
    }
    run(gas, cost, -1);
}

}
