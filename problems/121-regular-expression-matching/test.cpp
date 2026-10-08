#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const string& p, bool want) {
    check(Solution().isMatch(s, p), want, "s", s, "p", p);
}

static bool oracle(const string& s, const string& p) {
    return regex_match(s, regex(p));
}

static string repeat(const string& unit, int times) {
    string out;
    for (int i = 0; i < times; ++i) {
        out += unit;
    }
    return out;
}

TEST(examples) {
    run("abbbc", "ab*c", true);
    run("abcd", "a.c", false);
    run("zq", ".*", true);
}

TEST(edge_cases) {
    run("a", "a", true);
    run("a", "b", false);
    run("a", ".", true);
    run("aa", "a", false);
    run("a", "a*", true);
    run("a", "ab*", true);
    run("ab", ".*c", false);
    run("aaa", "a*a", true);
    run("aaa", "ab*a*c*a", true);
    run("a", "ab*a", false);
    run("aab", "c*a*b", true);
    run("mississippi", "mis*is*p*.", false);
    run("aaa", "aaaa", false);
    run("a", ".*..a*", false);
    run("bbbba", ".*a*a", true);
    run("ab", ".*..", true);
    run("aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s", true);
}

TEST(random) {
    Rng rng(1210);
    const vector<string> tokens{"a", "b", ".", "a*", "b*", ".*"};
    for (int iter = 0; iter < 150; ++iter) {
        string s = rng.str(rng(1, 8), "ab"), p;
        while (p.empty() || (p.size() < 12 && rng.coin(0.75))) {
            p += rng.pick(tokens);
        }
        run(s, p, oracle(s, p));
    }
}

TEST(large) {
    run(repeat("a", 19) + "b", repeat("a*", 10), false);
    run(repeat("a", 20), repeat("a*", 9) + ".b", false);
    run(repeat("a", 20), repeat("a*", 9) + "b", false);
    run(repeat("a", 20), repeat(".*", 9) + "c", false);
    run(repeat("a", 20), repeat("a*", 10), true);
    run(repeat("a", 20), repeat(".*", 9) + "a", true);
    run(repeat("ab", 10), repeat(".*", 9) + "b", true);
    run(repeat("ab", 10), repeat("a*b*", 5), false);
    run(repeat("ab", 10), repeat("a*b*", 4) + "ab", false);
    run(repeat("ab", 10), ".*a.*b.*a.*b.*a.*b", true);
}

}
