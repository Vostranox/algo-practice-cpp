#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static string printable() {
    string s;
    for (char c = 32; c < 127; ++c) {
        s += c;
    }
    return s;
}

static void run(const string& s, int want) {
    check(Solution().lengthOfLongestSubstring(s), want, "s", s);
}

static int brute(const string& s) {
    int best = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (static_cast<int>(set<char>(s.begin() + i, s.begin() + j).size()) == j - i) {
                best = max(best, j - i);
            }
        }
    }
    return best;
}

static string shuffled(string s, Rng& rng) {
    vector<char> v(s.begin(), s.end());
    rng.shuffle(v);
    return string(v.begin(), v.end());
}

TEST(examples) {
    run("zxyzxyz", 3);
    run("tmmzuxt", 5);
    run("bbbb", 1);
}

TEST(edge_cases) {
    run("", 0);
    run(" ", 1);
    run("  ", 1);
    run("a", 1);
    run("au", 2);
    run("abba", 2);
    run("dvdf", 3);
    run("a b c", 3);
    run("aab", 2);
    run("abcdefg", 7);
    run("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 52);
    run("Aa", 2);
    run("12!@12!@#", 5);
    run(printable(), 95);
}

TEST(random) {
    Rng rng(16);
    for (int i = 0; i < 400; ++i) {
        string s = rng.str(rng(0, 14), "abcd ");
        run(s, brute(s));
    }
}

TEST(large) {
    Rng rng(1616);
    const int n = 50000;
    const string all = printable();
    run(string(n, 'a'), 1);
    string cycle;
    while (static_cast<int>(cycle.size()) < n) {
        cycle += all;
    }
    run(cycle.substr(0, n), 95);
    string s = rng.str(n, "abcdefghij");
    s.replace(31000, 10, shuffled("abcdefghij", rng));
    run(s, 10);
    s = rng.str(n, all);
    s.replace(12345, 95, shuffled(all, rng));
    run(s, 95);
}

}
