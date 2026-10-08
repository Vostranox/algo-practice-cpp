#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(string s, bool want) {
    check(Solution().checkValidString(s), want, "s", s);
}

static bool balanced(const string& t) {
    int depth = 0;
    for (char c : t) {
        depth += c == '(' ? 1 : -1;
        if (depth < 0) return false;
    }
    return depth == 0;
}

static bool brute(const string& s) {
    vector<int> stars;
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        if (s[i] == '*') {
            stars.push_back(i);
        }
    }
    int ways = 1;
    for (size_t i = 0; i < stars.size(); ++i) {
        ways *= 3;
    }
    for (int code = 0; code < ways; ++code) {
        string t;
        for (int i = 0, c = code; i < static_cast<int>(s.size()); ++i) {
            if (s[i] != '*') {
                t += s[i];
            } else {
                if (c % 3 < 2) {
                    t += "()"[c % 3];
                }
                c /= 3;
            }
        }
        if (balanced(t)) return true;
    }
    return false;
}

TEST(examples) {
    run("(*()", true);
    run("*)(", false);
    run("**())", true);
}

TEST(edge_cases) {
    run("*", true);
    run("(", false);
    run(")", false);
    run("()", true);
    run(")(", false);
    run("(*", true);
    run("*)", true);
    run(")*", false);
    run("*(", false);
    run("**", true);
    run("((*)", true);
    run("(((*)", false);
    run("((*", false);
    run("(*)(", false);
    run("(*))", true);
    run("((**)", true);
    run("(()*))", true);
    run(")" + string(99, '*'), false);
}

TEST(random) {
    Rng rng(678);
    for (int done = 0; done < 800;) {
        string s = rng.str(rng(1, 12), "(()*)");
        if (count(s.begin(), s.end(), '*') > 7) continue;
        run(s, brute(s));
        ++done;
    }
}

static string rep(const string& part, int times) {
    string out;
    while (times--) {
        out += part;
    }
    return out;
}

TEST(large) {
    run(rep("*", 99) + "(", false);
    run("(" + rep("*", 98) + "(", false);
    run(rep("*", 50) + rep("(", 50), false);
    run(rep("*", 49) + rep(")", 50) + "*", false);
    run(rep("(", 51) + rep("*", 48) + ")", false);
    run(rep("*", 10) + rep(")", 11) + rep("*", 79), false);
    run(rep("(", 50) + rep("*", 49) + ")", true);
    run(rep("*", 50) + rep(")", 50), true);
    run(rep("(*", 50), true);
    run(rep("*", 100), true);
    run(rep("(", 34) + rep("*", 33) + rep(")", 33), true);
    run(rep("*(", 25) + rep("*)", 25), true);
    run(rep("(", 10) + rep("*", 40) + rep(")", 50), true);
}

}
