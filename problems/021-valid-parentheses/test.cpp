#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, bool want) {
    check(Solution().isValid(s), want, "s", s);
}

static bool brute(string s) {
    for (bool changed = true; changed;) {
        changed = false;
        for (const char* pair : {"()", "[]", "{}"}) {
            for (size_t i; (i = s.find(pair)) != string::npos;) {
                s.erase(i, 2);
                changed = true;
            }
        }
    }
    return s.empty();
}

static string rep(const string& s, int times) {
    string out;
    for (int i = 0; i < times; ++i) {
        out += s;
    }
    return out;
}

TEST(examples) {
    run("{[()()]}", true);
    run("([)]", false);
    run("(()", false);
}

TEST(edge_cases) {
    run("()", true);
    run("[]", true);
    run("{}", true);
    run("(", false);
    run(")", false);
    run("]", false);
    run(")(", false);
    run("(]", false);
    run("{)", false);
    run("((", false);
    run("))", false);
    run("()[]{}", true);
    run("([{}])", true);
    run("([{}]))", false);
    run("(([{}])", false);
    run("[(])", false);
    run("{[]}()[{()}]", true);
}

TEST(large) {
    run(rep("(", 5000) + rep(")", 5000), true);
    string nested = rep("([{", 1666) + rep("}])", 1666);
    run(nested, true);
    swap(nested[4998], nested[4999]);
    run(nested, false);
    run(rep("()", 5000), true);
    run(rep("(", 10000), false);
    run(rep("[", 4999) + rep("]", 5000) + "(", false);
    run(rep("{}", 2500) + rep("(", 2500) + rep(")", 2499) + "]", false);
}

TEST(random) {
    Rng rng(21);
    const vector<string> pairs = {"()", "[]", "{}"};
    for (int iter = 0; iter < 2000; ++iter) {
        string s;
        for (int k = rng(1, 8); k > 0; --k) {
            s.insert(rng(0, static_cast<int>(s.size())), rng.pick(pairs));
        }
        if (rng.coin(0.6)) {
            int how = rng(0, 2);
            if (how == 0) {
                s[rng(0, static_cast<int>(s.size()) - 1)] = "()[]{}"[rng(0, 5)];
            } else if (how == 1) {
                swap(s[rng(0, static_cast<int>(s.size()) - 1)], s[rng(0, static_cast<int>(s.size()) - 1)]);
            } else {
                s.erase(rng(0, static_cast<int>(s.size()) - 1), 1);
            }
        }
        if (!s.empty()) {
            run(s, brute(s));
        }
    }
}

}
