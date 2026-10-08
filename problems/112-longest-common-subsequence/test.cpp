#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& text1, const string& text2, int want) {
    check(Solution().longestCommonSubsequence(text1, text2), want, "text1", text1, "text2", text2);
}

static bool is_subsequence(const string& sub, const string& text) {
    size_t i = 0;
    for (char c : text) {
        if (i < sub.size() && sub[i] == c) {
            ++i;
        }
    }
    return i == sub.size();
}

static int brute(const string& text1, const string& text2) {
    int n = text1.size(), best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        string sub;
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {
                sub += text1[i];
            }
        }
        if (static_cast<int>(sub.size()) > best && is_subsequence(sub, text2)) {
            best = sub.size();
        }
    }
    return best;
}

static int suffix_table(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            lcs[i][j] = a[i] == b[j] ? lcs[i + 1][j + 1] + 1 : max(lcs[i + 1][j], lcs[i][j + 1]);
        }
    }
    return lcs[0][0];
}

static string repeat(const string& unit, int times) {
    string out;
    for (int i = 0; i < times; ++i) {
        out += unit;
    }
    return out;
}

TEST(examples) {
    run("stone", "longest", 3);
    run("abc", "abc", 3);
    run("abc", "xyz", 0);
}

TEST(edge_cases) {
    run("a", "a", 1);
    run("a", "b", 0);
    run("ab", "ba", 1);
    run("aaaa", "aa", 2);
    run("abcde", "ace", 3);
    run("bsbininm", "jmjkbkjkv", 1);
    run("xaybzc", "abc", 3);
    run("abc", "cba", 1);
}

TEST(random) {
    Rng rng(1120);
    for (int iter = 0; iter < 300; ++iter) {
        string t1 = rng.str(rng(1, 10), "abc"), t2 = rng.str(rng(1, 10), "abc");
        run(t1, t2, brute(t1, t2));
    }
}

TEST(large) {
    run(string(1000, 'a'), string(1000, 'b'), 0);
    run(repeat("abc", 333) + "a", string(1000, 'a'), 334);
    Rng rng(1121);
    string t1 = rng.str(1000, "abcd"), t2 = rng.str(1000, "abcd");
    run(t1, t2, suffix_table(t1, t2));
    t1 = rng.str(1000, "abcdefghijklmnopqrstuvwxyz");
    t2 = rng.str(300, "aeiou");
    run(t1, t2, suffix_table(t1, t2));
    run(t2, t1, suffix_table(t1, t2));
}

}
