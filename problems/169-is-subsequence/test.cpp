#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const string& t, bool want) {
    check(Solution().isSubsequence(s, t), want, "s", s, "t", t);
}

static bool brute(const string& s, const string& t) {
    int n = t.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) != static_cast<int>(s.size())) continue;
        string sub;
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {
                sub += t[i];
            }
        }
        if (sub == s) return true;
    }
    return false;
}

static bool by_lcs(const string& s, const string& t) {
    vector<int> prev(t.size() + 1, 0), cur(t.size() + 1, 0);
    for (char c : s) {
        for (size_t j = 0; j < t.size(); ++j) {
            cur[j + 1] = c == t[j] ? prev[j] + 1 : max(cur[j], prev[j + 1]);
        }
        swap(prev, cur);
    }
    return prev[t.size()] == static_cast<int>(s.size());
}

TEST(examples) {
    run("rot", "parrot", true);
    run("tar", "parrot", false);
    run("", "abc", true);
}

TEST(edge_cases) {
    run("", "", true);
    run("a", "", false);
    run("abc", "abc", true);
    run("abcd", "abc", false);
    run("aa", "a", false);
    run("aa", "bab", false);
    run("aa", "aba", true);
    run("ab", "ba", false);
    run("acb", "abc", false);
    run("bb", "abcb", true);
    run("z", "abcdefghijklmnopqrstuvwxyz", true);
    run("a", "zzzzzzzzza", true);
    run("q", "abcdefghijklmnoprstuvwxyz", false);
}

TEST(random) {
    Rng rng(392);
    for (int it = 0; it < 1000; ++it) {
        string t = rng.str(rng(0, 12), it % 2 ? "ab" : "abc");
        string s;
        if (rng.coin() && !t.empty()) {
            for (char c : t) {
                if (rng.coin()) {
                    s += c;
                }
            }
            if (!s.empty() && rng.coin(0.3)) {
                s[rng(0, static_cast<int>(s.size()) - 1)] = rng.coin() ? 'a' : 'c';
            }
        } else {
            s = rng.str(rng(0, 5), "abc");
        }
        run(s, t, brute(s, t));
    }
}

TEST(large) {
    string ab, ba;
    for (int i = 0; i < 5000; ++i) {
        ab += "ab";
    }
    for (int i = 0; i < 50; ++i) {
        ba += "ba";
    }
    run(ba, ab, true);
    string many_a = string(9999, 'a') + "b";
    run(string(99, 'a') + "b", many_a, true);
    run("ba", many_a, false);
    run(string(100, 'b'), many_a, false);
    Rng rng(39200);
    string t = rng.str(10000, "abcdefghijklmnopqrstuvwxyz");
    string z99;
    for (int i = 0; i < 10000; ++i) {
        z99 += i % 101 == 50 ? 'z' : t[i] == 'z' ? 'y' : t[i];
    }
    run(string(99, 'z'), z99, true);
    run(string(100, 'z'), z99, false);
    for (int it = 0; it < 6; ++it) {
        string s;
        for (int i = 0; i < 100; ++i) {
            s += t[rng(0, 9999)];
        }
        if (it % 2 == 0) {
            vector<int> pos;
            for (int i = 0; i < 100; ++i) {
                pos.push_back(rng(0, 9999));
            }
            s.clear();
            for (int p : sorted(pos)) {
                s += t[p];
            }
        }
        run(s, t, by_lcs(s, t));
    }
}

}
