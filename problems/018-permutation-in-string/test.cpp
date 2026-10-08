#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s1, const string& s2, bool want) {
    check(Solution().checkInclusion(s1, s2), want, "s1", s1, "s2", s2);
}

static bool brute(string s1, const string& s2) {
    sort(s1.begin(), s1.end());
    for (size_t i = 0; i + s1.size() <= s2.size(); ++i) {
        string w = s2.substr(i, s1.size());
        sort(w.begin(), w.end());
        if (w == s1) return true;
    }
    return false;
}

TEST(examples) {
    run("abc", "lecabee", true);
    run("abc", "lecaabee", false);
    run("abcd", "dcb", false);
}

TEST(edge_cases) {
    run("a", "a", true);
    run("a", "b", false);
    run("ab", "ab", true);
    run("ab", "ba", true);
    run("ab", "a", false);
    run("aab", "abab", true);
    run("aab", "abbab", false);
    run("adc", "dcda", true);
    run("xyz", "aaaaazyx", true);
    run("xyz", "zxyaaaaa", true);
    run("hello", "ooolleoooleh", false);
    run("aaa", "aabaa", false);
}

TEST(random) {
    Rng rng(18);
    for (int i = 0; i < 400; ++i) {
        string s1 = rng.str(rng(1, 4), "abc"), s2 = rng.str(rng(1, 10), "abc");
        run(s1, s2, brute(s1, s2));
    }
}

TEST(large) {
    Rng rng(1818);
    const int n = 10000;
    for (auto [m, pos] : vector<pair<int, int>>{{5000, 5000}, {3000, 6999}, {5000, 2500}, {7000, 3000}, {10000, 0}}) {
        string s1 = rng.str(m, "abcdefghijklm");
        string filler = rng.str(n, "nopqrstuvwxyz");
        vector<char> block(s1.begin(), s1.end());
        rng.shuffle(block);
        string s2 = filler.substr(0, pos) + string(block.begin(), block.end()) + filler.substr(pos + m);
        run(s1, s2, true);
        int j = rng(0, m - 1);
        block[j] = block[j] != 'a' ? 'a' : 'b';
        s2 = filler.substr(0, pos) + string(block.begin(), block.end()) + filler.substr(pos + m);
        run(s1, s2, false);
    }
}

}
