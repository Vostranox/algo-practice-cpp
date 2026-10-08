#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const string& t, bool want) {
    check(Solution().isIsomorphic(s, t), want, "s", s, "t", t);
}

static vector<int> shape(const string& s) {
    vector<int> out;
    for (size_t i = 0; i < s.size(); ++i) {
        out.push_back(s.find(s[i]));
    }
    return out;
}

static bool oracle(const string& s, const string& t) { return shape(s) == shape(t); }

static string printable() {
    string chars;
    for (char c = ' '; c <= '~'; ++c) {
        chars += c;
    }
    return chars;
}

TEST(examples) {
    run("abca", "zyxz", true);
    run("aab", "xyz", false);
    run("ab", "cc", false);
}

TEST(edge_cases) {
    run("a", "a", true);
    run("a", "b", true);
    run("ab", "ba", true);
    run("aa", "ab", false);
    run("ab", "aa", false);
    run("abc", "abc", true);
    run("abab", "baba", true);
    run("abab", "baab", false);
    run("1 2", "3 4", true);
    run("a b", "c c", false);
    run("  ", "!!", true);
    run("badc", "baba", false);
    run("x+y=z", "a-b=c", true);
    run("~~~A", "AAA~", true);
}

TEST(random) {
    Rng rng(174);
    for (int i = 0; i < 500; ++i) {
        int n = rng(1, 8);
        string s = rng.str(n, "abc"), t;
        if (rng.coin()) {
            t = rng.str(n, "xyz");
        } else {
            string image = rng.str(3, "xyz");
            for (char c : s) {
                t += image[c - 'a'];
            }
            if (rng.coin(0.2)) {
                t[rng(0, n - 1)] = 'x';
            }
        }
        run(s, t, oracle(s, t));
    }
}

TEST(large) {
    Rng rng(1740);
    string chars = printable();
    vector<char> perm(chars.begin(), chars.end());
    rng.shuffle(perm);
    string s = rng.str(50000, chars), t = s;
    for (char& c : t) {
        c = perm[c - ' '];
    }
    run(s, t, true);
    run(t, s, true);
    string bad = t;
    bad.back() = perm[(s.back() - ' ' + 1) % chars.size()];
    run(s, bad, oracle(s, bad));
    run(string(50000, 'a'), string(50000, 'b'), true);
    run(string(50000, 'a'), string(49999, 'b') + "c", false);
    run(rng.str(50000, "ab"), string(50000, 'q'), false);
}

}
