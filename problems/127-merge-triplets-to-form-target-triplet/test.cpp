#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Triplets = vector<vector<int>>;

static void run(const Triplets& triplets, const vector<int>& target, bool want) {
    Triplets t = triplets;
    vector<int> g = target;
    check(Solution().mergeTriplets(t, g), want, "triplets", triplets, "target", target);
}

static bool brute(const Triplets& triplets, const vector<int>& target) {
    int n = static_cast<int>(triplets.size());
    for (int mask = 1; mask < (1 << n); ++mask) {
        vector<int> m = {0, 0, 0};
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {
                for (int k = 0; k < 3; ++k) {
                    m[k] = max(m[k], triplets[i][k]);
                }
            }
        }
        if (m == target) return true;
    }
    return false;
}

TEST(examples) {
    run({{1, 4, 2}, {3, 1, 5}, {2, 3, 6}}, {3, 4, 5}, true);
    run({{4, 1, 1}, {1, 2, 6}}, {4, 2, 5}, false);
    run({{5, 5, 5}}, {5, 5, 5}, true);
}

TEST(edge_cases) {
    run({{1, 1, 1}}, {1, 1, 2}, false);
    run({{1, 1, 2}}, {1, 1, 2}, true);
    run({{2, 1, 1}, {1, 2, 1}, {1, 1, 2}}, {2, 2, 2}, true);
    run({{2, 2, 3}, {1, 1, 1}}, {2, 2, 2}, false);
    run({{2, 2, 1}, {1, 1, 3}}, {2, 2, 2}, false);
    run({{1000, 1, 1}, {1, 1000, 1}, {1, 1, 1000}}, {1000, 1000, 1000}, true);
    run({{3, 4, 5}, {3, 4, 5}}, {3, 4, 5}, true);
    run({{1, 2, 3}, {3, 2, 1}}, {3, 2, 3}, true);
    run({{1, 2, 3}, {3, 2, 1}}, {3, 3, 3}, false);
    run({{5, 1, 1}, {1, 5, 1}, {1, 1, 6}, {1, 1, 5}}, {5, 5, 5}, true);
    run({{2, 5, 3}, {5, 2, 4}}, {5, 5, 3}, false);
    run({{7, 7, 7}, {1, 1, 1}}, {1, 1, 1}, true);
}

TEST(random) {
    Rng rng(1899);
    for (int it = 0; it < 600; ++it) {
        int n = rng(1, 7);
        Triplets triplets(n);
        for (auto& t : triplets) {
            t = rng.ints(3, 1, 4);
        }
        vector<int> target;
        if (rng.coin()) {
            target = {0, 0, 0};
            for (auto& t : triplets) {
                if (rng.coin()) {
                    for (int k = 0; k < 3; ++k) {
                        target[k] = max(target[k], t[k]);
                    }
                }
            }
            for (int& x : target) {
                x = max(x, 1);
            }
            if (rng.coin()) {
                target[rng(0, 2)] = rng(1, 4);
            }
        } else {
            target = rng.ints(3, 1, 4);
        }
        run(triplets, target, brute(triplets, target));
    }
}

static vector<int> unusable(Rng& rng, const vector<int>& t) {
    vector<int> x(3);
    for (int i = 0; i < 3; ++i) {
        x[i] = rng.coin() ? t[i] : rng(1, 1000);
    }
    int k = rng(0, 2);
    x[k] = rng(t[k] + 1, 1000);
    return x;
}

static vector<int> below(Rng& rng, const vector<int>& t) {
    return {rng(1, t[0] - 1), rng(1, t[1] - 1), rng(1, t[2] - 1)};
}

const int n = 100000;

TEST(large) {
    Rng rng(3);
    vector<int> t = {500, 600, 700};
    Triplets filler;
    for (int i = 0; i < n - 3; ++i) {
        filler.push_back(rng.coin(0.7) ? unusable(rng, t) : below(rng, t));
    }
    Triplets triplets = filler;
    triplets.insert(triplets.end(), {{500, 1, 1}, {1, 600, 699}, {499, 599, 700}});
    rng.shuffle(triplets);
    run(triplets, t, true);
    triplets = filler;
    triplets.insert(triplets.end(), {{500, 1, 1}, {1, 600, 699}, {499, 599, 699}});
    rng.shuffle(triplets);
    run(triplets, t, false);
}

TEST(large_extremes) {
    Rng rng(13);
    vector<int> t = {500, 600, 700};
    Triplets triplets;
    for (int i = 0; i < n - 1; ++i) {
        triplets.push_back(unusable(rng, t));
    }
    triplets.push_back(t);
    rng.shuffle(triplets);
    run(triplets, t, true);
    vector<int> top = {1000, 1000, 1000};
    triplets.clear();
    for (int i = 0; i < n; ++i) {
        triplets.push_back({rng(1, 1000), rng(1, 999), rng(1, 1000)});
    }
    triplets[0][0] = triplets[1][2] = 1000;
    run(triplets, top, false);
    triplets[n - 1][1] = 1000;
    run(triplets, top, true);
}

}
