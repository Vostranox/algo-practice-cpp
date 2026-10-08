#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static vector<string> brute(int n) {
    vector<string> out;
    for (int mask = 0; mask < (1 << (2 * n)); ++mask) {
        string s;
        int depth = 0;
        for (int i = 0; i < 2 * n && depth >= 0; ++i) {
            bool open = mask >> i & 1;
            s += open ? '(' : ')';
            depth += open ? 1 : -1;
        }
        if (depth == 0 && static_cast<int>(s.size()) == 2 * n) {
            out.push_back(s);
        }
    }
    return out;
}

static void run(int n, const vector<string>& want) {
    vector<string> got = Solution().generateParenthesis(n);
    ensure(!has_duplicates(got), "the list contains duplicates", "n", n, "got", got);
    check(sorted(got), sorted(want), "n", n);
}

TEST(examples) {
    run(1, {"()"});
    run(2, {"(())", "()()"});
    run(3, {"((()))", "(()())", "(())()", "()(())", "()()()"});
}

TEST(small_against_brute_force) {
    for (int n = 1; n <= 5; ++n) {
        run(n, brute(n));
    }
}

TEST(large) {
    const int catalan[] = {1, 1, 2, 5, 14, 42, 132, 429, 1430};
    for (int n = 6; n <= 8; ++n) {
        vector<string> want = brute(n);
        if (static_cast<int>(want.size()) != catalan[n]) {
            fail("internal test error: brute force is wrong");
        }
        run(n, want);
    }
}

}
