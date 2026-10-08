#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static const map<char, string> KEYS = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
                                       {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

static void run(string digits, vector<string> want) {
    auto got = sorted(Solution().letterCombinations(digits));
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the string " + repr(*d) + " appears more than once", "digits", digits, "got", got);
    }
    check(got, sorted(want), "digits", digits);
}

static vector<string> oracle(const string& digits) {
    if (digits.empty()) return {};
    vector<string> out = {""};
    for (char d : digits) {
        vector<string> next;
        for (auto& prefix : out) {
            for (char c : KEYS.at(d)) {
                next.push_back(prefix + c);
            }
        }
        out = next;
    }
    return out;
}

TEST(examples) {
    run("47", {"gp", "gq", "gr", "gs", "hp", "hq", "hr", "hs", "ip", "iq", "ir", "is"});
    run("9", {"w", "x", "y", "z"});
    run("", {});
}

TEST(edge_cases) {
    run("2", {"a", "b", "c"});
    run("22", {"aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"});
    run("86", {"tm", "tn", "to", "um", "un", "uo", "vm", "vn", "vo"});
    run("68", {"mt", "mu", "mv", "nt", "nu", "nv", "ot", "ou", "ov"});
    run("7979", oracle("7979"));
    run("2345", oracle("2345"));
}

TEST(random) {
    Rng rng(17);
    for (int iter = 0; iter < 300; ++iter) {
        string digits = rng.str(rng(0, 4), "23456789");
        run(digits, oracle(digits));
    }
}

}
