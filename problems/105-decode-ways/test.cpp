#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, int want) {
    check(Solution().numDecodings(s), want, "s", s);
}

static int brute(const string& s, size_t pos = 0) {
    if (pos == s.size()) return 1;
    int count = 0;
    for (size_t len : {1, 2}) {
        if (pos + len > s.size()) continue;
        string piece = s.substr(pos, len);
        int v = stoi(piece);
        if (piece[0] != '0' && v >= 1 && v <= 26) {
            count += brute(s, pos + len);
        }
    }
    return count;
}

static int64_t fib(int k) {
    int64_t a = 0, b = 1;
    for (int i = 0; i < k; ++i) {
        int64_t c = a + b;
        a = b;
        b = c;
    }
    return a;
}

static string repeat(const string& unit, int times) {
    string out;
    for (int i = 0; i < times; ++i) {
        out += unit;
    }
    return out;
}

TEST(examples) {
    run("1125", 5);
    run("2101", 1);
    run("06", 0);
}

TEST(edge_cases) {
    run("0", 0);
    run("1", 1);
    run("10", 1);
    run("20", 1);
    run("30", 0);
    run("100", 0);
    run("101", 1);
    run("110", 1);
    run("26", 2);
    run("27", 1);
    run("2626", 4);
    run("1001", 0);
    run("123", 3);
    run("00", 0);
    run("9", 1);
}

TEST(random) {
    Rng rng(1050);
    for (int iter = 0; iter < 500; ++iter) {
        string s = rng.str(rng(1, 14), rng.coin() ? "0112223456789" : "0126");
        run(s, brute(s));
    }
}

TEST(large) {
    run(string(45, '1') + "0" + string(54, '3'), static_cast<int>(fib(45)));
    run(repeat(string(9, '1') + "0", 5) + string(50, '3'), 34 * 34 * 34 * 34 * 34);
    run(string(44, '2') + "0" + string(55, '7'), static_cast<int>(fib(44)));
}

}
