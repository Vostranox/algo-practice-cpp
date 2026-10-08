#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, int numRows, const string& want) {
    check(Solution().convert(s, numRows), want, "s", s, "numRows", numRows);
}

static string oracle(const string& s, int numRows) {
    vector<string> grid(numRows, string(s.size(), ' '));
    int r = 0, c = 0;
    bool down = true;
    for (char ch : s) {
        grid[r][c] = ch;
        if (numRows == 1) {
            ++c;
        } else if (down && r == numRows - 1) {
            down = false, --r, ++c;
        } else if (down) {
            ++r;
        } else if (r == 0) {
            down = true, ++r;
        } else {
            --r, ++c;
        }
    }
    string out;
    for (const string& row : grid) {
        for (char ch : row) {
            if (ch != ' ') {
                out += ch;
            }
        }
    }
    return out;
}

TEST(examples) {
    run("ABCDEFGHIJ", 3, "AEIBDFHJCG");
    run("ABCDEFGHIJ", 4, "AGBFHCEIDJ");
    run("hello", 1, "hello");
}

TEST(edge_cases) {
    run("z", 1, "z");
    run("z", 1000, "z");
    run("ab", 5, "ab");
    run("abc", 3, "abc");
    run("abcd", 3, "abdc");
    run("abcdef", 2, "acebdf");
    run("a,b.c", 2, "abc,.");
    run("Zig.Zag,Ok", 5, "ZOi,kgg.aZ");
}

TEST(random) {
    Rng rng(166);
    for (int i = 0; i < 500; ++i) {
        int n = rng(1, 20), rows = rng(1, 8);
        string s = rng.str(n, "abcdefghijKLMN,.");
        run(s, rows, oracle(s, rows));
    }
}

TEST(large) {
    Rng rng(1660);
    string s = rng.str(1000, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.");
    for (int rows : {1, 2, 3, 7, 499, 500, 501, 999, 1000}) {
        run(s, rows, oracle(s, rows));
    }
    run(s, 1000, s);
    run(s, 1, s);
}

}
