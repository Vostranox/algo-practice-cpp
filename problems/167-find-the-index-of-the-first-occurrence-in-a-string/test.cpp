#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& haystack, const string& needle, int want) {
    check(Solution().strStr(haystack, needle), want, "haystack", haystack, "needle", needle);
}

static int brute(const string& h, const string& nd) {
    for (size_t i = 0; i + nd.size() <= h.size(); ++i) {
        size_t j = 0;
        while (j < nd.size() && h[i + j] == nd[j]) {
            ++j;
        }
        if (j == nd.size()) return i;
    }
    return -1;
}

TEST(examples) {
    run("hello world", "o", 4);
    run("mississippi", "issip", 4);
    run("abc", "abcd", -1);
}

TEST(edge_cases) {
    run("a", "a", 0);
    run("a", "b", -1);
    run("same", "same", 0);
    run("abcde", "cde", 2);
    run("abcde", "abc", 0);
    run("aaaa", "aa", 0);
    run("aaab", "aab", 1);
    run("abababc", "ababc", 2);
    run("abcabd", "abd", 3);
    run("xyz", "xyzz", -1);
    run("abcdef", "acd", -1);
    run("ab", "b", 1);
}

TEST(random) {
    Rng rng(167);
    for (int i = 0; i < 500; ++i) {
        string h = rng.str(rng(1, 20), "ab"), nd;
        if (rng.coin() && h.size() > 1) {
            int start = rng(0, static_cast<int>(h.size()) - 1);
            nd = h.substr(start, rng(1, static_cast<int>(h.size()) - start));
            if (rng.coin()) {
                nd[rng(0, static_cast<int>(nd.size()) - 1)] ^= 'a' ^ 'b';
            }
        } else {
            nd = rng.str(rng(1, 5), "ab");
        }
        run(h, nd, brute(h, nd));
    }
}

TEST(large) {
    run(string(9999, 'a') + "b", string(4999, 'a') + "b", 5000);
    run(string(10000, 'a'), string(4999, 'a') + "b", -1);
    run(string(10000, 'a'), string(10000, 'a'), 0);
    run(string(9999, 'a') + "b", string(10000, 'a'), -1);
    string ab;
    for (int i = 0; i < 5000; ++i) {
        ab += "ab";
    }
    run(ab, ab.substr(0, 4000) + "b", -1);
    run(ab, ab.substr(1, 3001), 1);
    Rng rng(1670);
    string h = rng.str(10000, "abc");
    string nd = h.substr(7000, 300);
    run(h, nd, brute(h, nd));
}

}
