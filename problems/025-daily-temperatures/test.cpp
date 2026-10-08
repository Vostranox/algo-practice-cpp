#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& temps, const vector<int>& want) {
    vector<int> arg = temps;
    check(Solution().dailyTemperatures(arg), want, "temperatures", temps);
}

static vector<int> brute(const vector<int>& t) {
    vector<int> out(t.size(), 0);
    for (size_t i = 0; i < t.size(); ++i) {
        for (size_t j = i + 1; j < t.size(); ++j) {
            if (t[j] > t[i]) {
                out[i] = static_cast<int>(j - i);
                break;
            }
        }
    }
    return out;
}

TEST(examples) {
    run({60, 58, 59, 64, 61, 61, 70}, {3, 1, 1, 3, 2, 1, 0});
    run({40, 50, 60}, {1, 1, 0});
    run({90, 80, 80, 70}, {0, 0, 0, 0});
}

TEST(edge_cases) {
    run({30}, {0});
    run({100}, {0});
    run({30, 100}, {1, 0});
    run({100, 30}, {0, 0});
    run({50, 50, 50}, {0, 0, 0});
    run({50, 50, 51}, {2, 1, 0});
    run({70, 40, 50, 60, 80}, {4, 1, 1, 1, 0});
    run({31, 30, 31, 30, 32}, {4, 1, 2, 1, 0});
}

TEST(random) {
    Rng rng(25);
    for (int iter = 0; iter < 2000; ++iter) {
        int n = rng(1, 40);
        int lo = rng(30, 100);
        int hi = min(100, lo + rng.pick(vector<int>{1, 2, 5, 70}));
        vector<int> temps = rng.ints(n, lo, hi);
        run(temps, brute(temps));
    }
}

TEST(large) {
    const int n = 100000;
    run(vector<int>(n, 100), vector<int>(n, 0));
    vector<int> temps(n, 50), want(n);
    temps.back() = 51;
    for (int i = 0; i < n; ++i) {
        want[i] = n - 1 - i;
    }
    run(temps, want);
    const int len = 71, blocks = n / len;
    temps.clear();
    want.clear();
    for (int b = 0; b < blocks; ++b) {
        for (int j = 0; j < len; ++j) {
            temps.push_back(100 - j);
            want.push_back(j == 0 || b == blocks - 1 ? 0 : len - j);
        }
    }
    run(temps, want);
}

}
