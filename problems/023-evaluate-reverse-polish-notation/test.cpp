#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<string>& tokens, int want) {
    vector<string> arg = tokens;
    check(Solution().evalRPN(arg), want, "tokens", tokens);
}

static vector<string> rep(const vector<string>& v, int times) {
    vector<string> out;
    for (int i = 0; i < times; ++i) {
        out.insert(out.end(), v.begin(), v.end());
    }
    return out;
}

static vector<string> operator+(vector<string> a, const vector<string>& b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

TEST(examples) {
    run({"3", "4", "+", "5", "*"}, 35);
    run({"20", "6", "-7", "+", "/"}, -20);
    run({"-9", "4", "/", "6", "2", "-", "*"}, -8);
}

TEST(division_truncates_toward_zero) {
    run({"7", "2", "/"}, 3);
    run({"-7", "2", "/"}, -3);
    run({"7", "-2", "/"}, -3);
    run({"-7", "-2", "/"}, 3);
    run({"1", "3", "/"}, 0);
    run({"-1", "3", "/"}, 0);
    run({"1", "-3", "/"}, 0);
    run({"-6", "3", "/"}, -2);
    run({"0", "-5", "/"}, 0);
    run({"2", "10", "/"}, 0);
    run({"-200", "7", "/", "3", "/"}, -9);
}

TEST(edge_cases) {
    run({"42"}, 42);
    run({"-7"}, -7);
    run({"0"}, 0);
    run({"3", "5", "-"}, -2);
    run({"4", "-3", "-"}, 7);
    run({"-4", "-3", "*"}, 12);
    run({"5", "1", "2", "+", "4", "*", "+", "3", "-"}, 14);
    run({"200", "200", "*", "200", "*"}, 8000000);
    run({"-200", "-200", "*", "-200", "*", "200", "*"}, -1600000000);
}

TEST(large) {
    run(vector<string>{"1"} + rep({"1", "+"}, 4999), 5000);
    run(rep({"2"}, 5000) + rep({"+"}, 4999), 10000);
    run(rep({"1"}, 5000) + rep({"-"}, 4999), 0);
    run(rep({"7"}, 5001) + rep({"-"}, 4998) + vector<string>{"+", "-"}, -7);
    run(vector<string>{"1"} + rep({"-3", "*", "2", "/"}, 2400), 1);
}

static int64_t random_expr(Rng& rng, int size, vector<string>& out) {
    if (size == 1) {
        int v = rng(-200, 200);
        out.push_back(to_string(v));
        return v;
    }
    int left = rng(1, size - 1);
    int64_t lv = random_expr(rng, left, out);
    size_t mark = out.size();
    int64_t rv = random_expr(rng, size - left, out);
    vector<string> ops = {"+", "-", "*", "/"};
    rng.shuffle(ops);
    for (const string& op : ops) {
        if (op == "/" && rv == 0) continue;
        int64_t v = op == "+" ? lv + rv : op == "-" ? lv - rv : op == "*" ? lv * rv : lv / rv;
        if (INT_MIN <= v && v <= INT_MAX) {
            out.push_back(op);
            return v;
        }
    }
    out.resize(mark);
    out.push_back("0");
    out.push_back("+");
    return lv;
}

TEST(random) {
    Rng rng(23);
    for (int iter = 0; iter < 2000; ++iter) {
        vector<string> tokens;
        int64_t value = random_expr(rng, rng(1, 12), tokens);
        run(tokens, static_cast<int>(value));
    }
    for (int iter = 0; iter < 5; ++iter) {
        vector<string> tokens;
        int64_t value = random_expr(rng, 5000, tokens);
        run(tokens, static_cast<int>(value));
    }
}

}
