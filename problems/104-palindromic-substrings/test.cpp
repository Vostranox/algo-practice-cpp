#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, int want) {
    check(Solution().countSubstrings(s), want, "s", s);
}

static int brute(const string& s) {
    int count = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            string sub = s.substr(i, j - i);
            count += equal(sub.begin(), sub.end(), sub.rbegin());
        }
    }
    return count;
}

static int64_t manacher_count(const string& s) {
    string t = "#";
    for (char c : s) {
        t += string(1, c) + "#";
    }
    int m = t.size(), center = 0, right = 0;
    vector<int> rad(m, 0);
    int64_t total = 0;
    for (int i = 0; i < m; ++i) {
        if (i < right) {
            rad[i] = min(right - i, rad[2 * center - i]);
        }
        while (i - rad[i] - 1 >= 0 && i + rad[i] + 1 < m && t[i - rad[i] - 1] == t[i + rad[i] + 1]) {
            ++rad[i];
        }
        if (i + rad[i] > right) {
            center = i, right = i + rad[i];
        }
        total += (rad[i] + 1) / 2;
    }
    return total;
}

TEST(examples) {
    run("level", 7);
    run("abba", 6);
    run("xyz", 3);
}

TEST(edge_cases) {
    run("q", 1);
    run("qq", 3);
    run("qp", 2);
    run("aaa", 6);
    run("aba", 4);
    run("abab", 6);
}

TEST(random) {
    Rng rng(1040);
    for (int iter = 0; iter < 400; ++iter) {
        string s = rng.str(rng(1, 15), rng.coin(0.6) ? "ab" : "abc");
        run(s, brute(s));
    }
}

TEST(large) {
    run(string(1000, 'a'), 1000 * 1001 / 2);
    string ab;
    for (int i = 0; i < 500; ++i) {
        ab += "ab";
    }
    run(ab, 250500);
    Rng rng(1041);
    for (string alphabet : {"ab", "abc", "abcdefghijklmnopqrstuvwxyz"}) {
        string s = rng.str(1000, alphabet);
        run(s, static_cast<int>(manacher_count(s)));
    }
}

}
