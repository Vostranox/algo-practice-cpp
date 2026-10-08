#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static const string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static void run(const string& s, int k, int want) {
    check(Solution().characterReplacement(s, k), want, "s", s, "k", k);
}

static int brute(const string& s, int k) {
    int best = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        int count[26] = {}, top = 0;
        for (int j = i; j < n; ++j) {
            top = max(top, ++count[s[j] - 'A']);
            if (j - i + 1 - top <= k) {
                best = max(best, j - i + 1);
            }
        }
    }
    return best;
}

static int oracle(const string& s, int k) {
    int n = s.size(), best = 0;
    for (char c : UPPER) {
        vector<int> others = {-1};
        for (int i = 0; i < n; ++i) {
            if (s[i] != c) {
                others.push_back(i);
            }
        }
        others.push_back(n);
        int m = static_cast<int>(others.size()) - 2;
        if (m <= k) return n;
        for (int i = 0; i + k + 1 < static_cast<int>(others.size()); ++i) {
            best = max(best, others[i + k + 1] - others[i] - 1);
        }
    }
    return best;
}

TEST(examples) {
    run("XYYX", 2, 4);
    run("AAABABB", 1, 5);
    run("BAAAB", 0, 3);
}

TEST(edge_cases) {
    run("A", 0, 1);
    run("A", 1, 1);
    run("AB", 0, 1);
    run("AB", 1, 2);
    run("ABAB", 2, 4);
    run("ABBB", 2, 4);
    run("ABCDEFG", 2, 3);
    run("ABCDEFG", 7, 7);
    run("BBABAA", 1, 4);
    run("ZZZZ", 0, 4);
    run("ABBAAAB", 0, 3);
}

TEST(random) {
    Rng rng(17);
    for (int i = 0; i < 300; ++i) {
        string s = rng.str(rng(1, 12), "ABC");
        int k = rng(0, static_cast<int>(s.size()));
        run(s, k, brute(s, k));
    }
}

TEST(large) {
    Rng rng(1717);
    const int n = 100000;
    run(string(n, 'A'), 0, n);
    string ab;
    for (int i = 0; i < n / 2; ++i) {
        ab += "AB";
    }
    run(ab, 25000, 50001);
    run(string(30000, 'B') + string(40000, 'A') + string(30000, 'B'), 100, 40100);
    string s = rng.str(n, UPPER);
    run(s, 0, oracle(s, 0));
    s = rng.str(n, "AB");
    run(s, 1000, oracle(s, 1000));
    s = rng.str(n, "ABCDE");
    run(s, 30000, oracle(s, 30000));
}

}
