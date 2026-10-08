#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, int want) {
    check(Solution().calculate(s), want, "s", s);
}

static string rep(const string& s, int times) {
    string out;
    for (int i = 0; i < times; ++i) {
        out += s;
    }
    return out;
}

static void spaces(Rng& rng, string& out, double p) {
    while (rng.coin(p)) {
        out += ' ';
    }
}

static int64_t gen(Rng& rng, int count, int max_num, double space_p, string& out) {
    int64_t value = 0;
    int sign = 1;
    spaces(rng, out, space_p);
    if (rng.coin(0.2)) {
        out += '-';
        sign = -1;
        spaces(rng, out, space_p);
    }
    for (bool first = true; count > 0; first = false) {
        if (!first) {
            sign = rng.coin() ? 1 : -1;
            spaces(rng, out, space_p);
            out += sign > 0 ? '+' : '-';
            spaces(rng, out, space_p);
        }
        int take = rng.coin(0.6) ? 1 : rng(1, count);
        count -= take;
        int64_t operand;
        if (take == 1 && rng.coin(0.7)) {
            operand = rng(0, max_num);
            out += to_string(operand);
        } else {
            out += '(';
            operand = gen(rng, take, max_num, space_p, out);
            spaces(rng, out, space_p);
            out += ')';
        }
        value += sign * operand;
    }
    return value;
}

TEST(examples) {
    run("7 - (2 + 3) + 1", 3);
    run("-(4 - (1 + 9))", 6);
    run(" 12 ", 12);
}

TEST(edge_cases) {
    run("0", 0);
    run("   7", 7);
    run("0-0", 0);
    run("10 - 2 - 3", 5);
    run("1 - (2 - 3)", 2);
    run("3-(2-(1-(4-5)))", 3);
    run("5 - (1 + 1) - (1 + 1)", 1);
    run("1 + (2 + (3 + (4 + 5)))", 15);
    run("(1)", 1);
    run("((7))", 7);
    run("(((1)))+(((2)))", 3);
    run("12345678 + 87654321", 99999999);
}

TEST(unary_minus) {
    run("-5", -5);
    run("- 5 + 2", -3);
    run("-(2+3)", -5);
    run("1-(-2)", 3);
    run("-(-(-(4)))", -4);
    run("- (3 + (4 - 5))", -2);
    run("(-1) - (-1)", 0);
    run("-(1)-(2)", -3);
    run("(  -  8  )", -8);
    run("2-(-(3))", 5);
}

TEST(int_limits) {
    run("2147483647", INT_MAX);
    run("-2147483647", -INT_MAX);
    run("(0 - 2147483647)", -INT_MAX);
    run("-(-2147483647)", INT_MAX);
    run("1000000000 + 1000000000 - 147483647", 1852516353);
    run("2147483646 + 1", INT_MAX);
}

TEST(random) {
    Rng rng(224);
    for (int it = 0; it < 3000; ++it) {
        string s;
        int64_t value = gen(rng, rng(1, 10), it % 3 ? 20 : 1000000, 0.3, s);
        spaces(rng, s, 0.3);
        run(s, static_cast<int>(value));
    }
}

TEST(large_deep) {
    run(rep("(", 149999) + "42" + rep(")", 149999), 42);
    run(rep("-(", 99999) + "7" + rep(")", 99999), -7);
    run(rep("-(", 99998) + "7" + rep(")", 99998), 7);
    Rng rng(22400);
    for (int it = 0; it < 2; ++it) {
        const int depth = 74999;
        vector<int> d(depth + 1);
        vector<char> op(depth);
        string s;
        for (int i = 0; i < depth; ++i) {
            d[i] = rng(1, 9);
            op[i] = it == 0 || rng.coin() ? '-' : '+';
            s += to_string(d[i]) + op[i] + "(";
        }
        d[depth] = rng(1, 9);
        s += to_string(d[depth]) + rep(")", depth);
        int64_t value = d[depth];
        for (int i = depth - 1; i >= 0; --i) {
            value = op[i] == '-' ? d[i] - value : d[i] + value;
        }
        run(s, static_cast<int>(value));
    }
}

TEST(large_flat) {
    Rng rng(22401);
    for (int it = 0; it < 2; ++it) {
        string s = to_string(rng(0, 9999));
        int64_t value = stoll(s);
        while (s.size() < 299980) {
            int x = rng(0, 9999);
            bool minus = it == 0 ? rng.coin() : true;
            s += it == 0 && rng.coin(0.3) ? (minus ? " - " : " + ") : (minus ? "-" : "+");
            s += to_string(x);
            value += minus ? -x : x;
        }
        run(s, static_cast<int>(value));
    }
}

TEST(large_random) {
    Rng rng(22402);
    for (int it = 0; it < 3; ++it) {
        string s;
        int64_t value = gen(rng, 30000, 9999, 0.1, s);
        ensure(s.size() <= 300000, "test generator made an expression that is too long", "length", s.size());
        run(s, static_cast<int>(value));
    }
}

}
