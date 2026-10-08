#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static const string ALNUM = "abcdefghijklmnopqrstuvwxyz0123456789";
static const string JUNK = " .,!?;:'\"-_()[]{}@#$%^&*/\\|`~+=<>";

static void run(const string& s, bool want) {
    check(Solution().isPalindrome(s), want, "s", s);
}

static bool oracle(const string& s) {
    string kept;
    for (unsigned char c : s) {
        if (isalnum(c)) {
            kept += static_cast<char>(tolower(c));
        }
    }
    return kept == string(kept.rbegin(), kept.rend());
}

static string build(const string& core, Rng& rng) {
    string out;
    for (char c : core) {
        if (rng.coin(0.3)) {
            out += JUNK[rng(0, static_cast<int>(JUNK.size()) - 1)];
        }
        out += rng.coin() ? static_cast<char>(toupper(static_cast<unsigned char>(c))) : c;
    }
    return out;
}

TEST(examples) {
    run("Was it a car, or a cat I saw?", true);
    run("ab2a", false);
    run(" .,! ", true);
}

TEST(edge_cases) {
    run(" ", true);
    run("a", true);
    run("aA", true);
    run("0p", false);
    run("a_a", true);
    run("ab_", false);
    run("9 9", true);
    run("a.b,A", true);
    run("No lemon, no melon", true);
    run("12:21", true);
    run("abcxcbz", false);
    run("ab", false);
    run("Ab!ba", true);
}

TEST(random) {
    Rng rng(10);
    for (int i = 0; i < 400; ++i) {
        string s;
        if (rng.coin()) {
            string half = rng.str(rng(0, 5), "aAbB1 .,");
            string mirror(half.rbegin(), half.rend());
            for (char& c : mirror) {
                c = isupper(static_cast<unsigned char>(c)) ? tolower(c) : toupper(c);
            }
            s = half + rng.str(rng(0, 1), "xX?") + mirror;
        } else {
            s = rng.str(rng(1, 10), "aAbB1 .,");
        }
        if (s.empty()) {
            s = " ";
        }
        run(s, oracle(s));
    }
}

TEST(large) {
    Rng rng(1010);
    string half = rng.str(70000, ALNUM);
    string core = half + "z" + string(half.rbegin(), half.rend());
    run(build(core, rng), true);
    core[40000] = core[40000] != '7' ? '7' : '8';
    run(build(core, rng), false);
}

}
