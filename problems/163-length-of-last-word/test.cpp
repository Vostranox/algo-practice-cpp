#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, int want) {
    check(Solution().lengthOfLastWord(s), want, "s", s);
}

static int oracle(const string& s) {
    istringstream in(s);
    string word, last;
    while (in >> word) {
        last = word;
    }
    return last.size();
}

TEST(examples) {
    run("open the door", 4);
    run("  ab cde   ", 3);
    run("x", 1);
}

TEST(edge_cases) {
    run("Hello", 5);
    run("   Hello", 5);
    run("Hello   ", 5);
    run(" a ", 1);
    run("keep  going   on", 2);
    run("long words a", 1);
    run("a bb ccc dddd", 4);
    run("ABC def GHIJ  ", 4);
    run("xyz  w", 1);
}

TEST(random) {
    Rng rng(163);
    for (int i = 0; i < 500; ++i) {
        string s = rng.str(rng(1, 15), "ab   ");
        if (s.find('a') == string::npos && s.find('b') == string::npos) {
            s[rng(0, static_cast<int>(s.size()) - 1)] = 'a';
        }
        run(s, oracle(s));
    }
}

TEST(large) {
    run(string(9999, ' ') + "z", 1);
    run("q" + string(9999, ' '), 1);
    run(string(10000, 'w'), 10000);
    run(" " + string(9998, 'w') + " ", 9998);
    Rng rng(1630);
    for (int iter = 0; iter < 5; ++iter) {
        string s = rng.str(10000, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ    ");
        s[rng(0, 9999)] = 'k';
        run(s, oracle(s));
    }
}

}
