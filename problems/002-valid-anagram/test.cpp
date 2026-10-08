#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const string& t, bool want) {
    check(Solution().isAnagram(s, t), want, "s", s, "t", t);
}

static string shuffled(const string& s, Rng& rng) {
    vector<char> v(s.begin(), s.end());
    rng.shuffle(v);
    return string(v.begin(), v.end());
}

static bool oracle(string a, string b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

TEST(examples) {
    run("listen", "silent", true);
    run("dusty", "study", true);
    run("abb", "aab", false);
}

TEST(edge_cases) {
    run("a", "a", true);
    run("a", "b", false);
    run("ab", "a", false);
    run("a", "ab", false);
    run("aa", "a", false);
    run("abc", "abcc", false);
    run("zzzz", "zzzz", true);
    run("abcd", "dcbae", false);
    run("aabbcc", "abcabc", true);
    run("aabbcc", "aabbcd", false);
}

TEST(random) {
    Rng rng(2);
    for (int i = 0; i < 400; ++i) {
        string s = rng.str(rng(1, 8), "abc");
        string t = rng.coin() ? shuffled(s, rng) : rng.str(rng(1, 8), "abc");
        run(s, t, oracle(s, t));
    }
}

TEST(large) {
    Rng rng(22);
    string s = rng.str(50000, "abcdefghijklmnopqrstuvwxyz");
    string t = shuffled(s, rng);
    run(s, t, true);
    size_t i = t.find_first_not_of('q');
    t[i] = 'q';
    run(s, t, false);
}

}
