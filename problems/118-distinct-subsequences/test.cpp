#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const string& t, int want) {
    check(Solution().numDistinct(s, t), want, "s", s, "t", t);
}

static int brute(const string& s, const string& t) {
    int n = s.size(), count = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) != static_cast<int>(t.size())) continue;
        string pick;
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {
                pick += s[i];
            }
        }
        count += pick == t;
    }
    return count;
}

static int64_t tables(const string& s, const string& t, bool& fits) {
    const int64_t CAP = int64_t{1} << 40;
    int n = s.size(), m = t.size();
    int64_t biggest = 0;
    vector<vector<int64_t>> pre(n + 1, vector<int64_t>(m + 1, 0)), suf = pre;
    for (int i = 0; i <= n; ++i) {
        pre[i][0] = suf[i][m] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            pre[i][j] = min(CAP, pre[i - 1][j] + (s[i - 1] == t[j - 1] ? pre[i - 1][j - 1] : 0));
            biggest = max(biggest, pre[i][j]);
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            suf[i][j] = min(CAP, suf[i + 1][j] + (s[i] == t[j] ? suf[i + 1][j + 1] : 0));
            biggest = max(biggest, suf[i][j]);
        }
    }
    fits = biggest <= INT_MAX;
    return pre[n][m];
}

static string block(char c, int len) { return string(len, c); }

TEST(examples) {
    run("bagbag", "bag", 4);
    run("aaa", "aa", 3);
    run("abc", "abd", 0);
}

TEST(edge_cases) {
    run("a", "a", 1);
    run("a", "b", 0);
    run("ab", "abc", 0);
    run("abc", "abc", 1);
    run("Aa", "a", 1);
    run("aAaA", "aA", 3);
    run("rabbbit", "rabbit", 3);
    run("babgbag", "bag", 5);
    run("xyz", "zyx", 0);
}

TEST(random) {
    Rng rng(1180);
    for (int iter = 0; iter < 300; ++iter) {
        string s = rng.str(rng(1, 13), "ab"), t = rng.str(rng(1, 4), "ab");
        run(s, t, brute(s, t));
    }
}

TEST(large) {
    run(block('a', 333) + block('b', 333) + block('c', 334), "abc", 333 * 333 * 334);
    run(block('a', 1000), "aaa", 1000 * 999 * 998 / 6);
    run(block('a', 1000), "aaab", 0);
    run(block('a', 500) + block('b', 500), "aab", 500 * 499 / 2 * 500);
    string aA;
    for (int i = 0; i < 500; ++i) {
        aA += "aA";
    }
    run(aA, "aA", 500 * 501 / 2);
    Rng rng(1181);
    string s999 = rng.str(999, "abcdefghijklmnopqrstuvwxyz");
    run(s999, s999 + "q", 0);
    for (int iter = 0; iter < 3;) {
        string s = rng.str(1000, "abcdefghijklmnopqrstuvwxyz");
        vector<int> pos(1000);
        iota(pos.begin(), pos.end(), 0);
        rng.shuffle(pos);
        pos.resize(rng(5, 8));
        sort(pos.begin(), pos.end());
        string t;
        for (int p : pos) {
            t += s[p];
        }
        bool fits;
        int64_t want = tables(s, t, fits);
        if (!fits) continue;
        run(s, t, static_cast<int>(want));
        ++iter;
    }
}

TEST(big_intermediate_counts) {
    run(block('a', 999) + "b", block('a', 998) + "b", 999);
    run(block('a', 1000), block('a', 500) + "b", 0);
}

}
