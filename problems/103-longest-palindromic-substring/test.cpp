#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, int wantLen) {
    string got = Solution().longestPalindrome(s);
    ensure(s.find(got) != string::npos, "the answer is not a substring of s", "s", s, "got", got);
    ensure(equal(got.begin(), got.end(), got.rbegin()), "the answer is not a palindrome", "s", s, "got", got);
    ensure(static_cast<int>(got.size()) == wantLen,
           "the answer has length " + to_string(got.size()) + ", but the longest palindromic substring has length " +
               to_string(wantLen),
           "s", s, "got", got);
}

static int brute_len(const string& s) {
    int best = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            string sub = s.substr(i, j - i);
            if (equal(sub.begin(), sub.end(), sub.rbegin())) {
                best = max(best, j - i);
            }
        }
    }
    return best;
}

static int manacher_len(const string& s) {
    string t = "#";
    for (char c : s) {
        t += string(1, c) + "#";
    }
    int m = t.size(), center = 0, right = 0;
    vector<int> rad(m, 0);
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
    }
    return *max_element(rad.begin(), rad.end());
}

static string repeat(const string& unit, int times) {
    string out;
    for (int i = 0; i < times; ++i) {
        out += unit;
    }
    return out;
}

TEST(examples) {
    run("tracecars", 7);
    run("cabbad", 4);
    run("pqr", 1);
}

TEST(edge_cases) {
    run("z", 1);
    run("zz", 2);
    run("zy", 1);
    run("Aa", 1);
    run("aAa", 3);
    run("12321x", 5);
    run("abacdfgdcaba", 3);
    run("xabbay", 4);
    run("abcbaqabba", 5);
    run("aaaa", 4);
}

TEST(random) {
    Rng rng(1030);
    for (int iter = 0; iter < 400; ++iter) {
        string s = rng.str(rng(1, 14), rng.coin(0.6) ? "ab" : "abc");
        run(s, brute_len(s));
    }
}

TEST(large) {
    run(string(1000, 'a'), 1000);
    run(repeat("ab", 500), 999);
    run(repeat("abc", 333) + "a", 1);
    Rng rng(1031);
    string half = rng.str(150, "xyz");
    string mirrored(half.rbegin(), half.rend());
    run(repeat("abc", 100) + half + mirrored + repeat("abc", 100) + string(99, 'd'), 300);
    for (string alphabet : {"ab", "abc", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"}) {
        string s = rng.str(1000, alphabet);
        run(s, manacher_len(s));
    }
}

}
