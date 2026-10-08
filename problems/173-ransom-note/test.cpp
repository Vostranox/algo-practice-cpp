#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& ransomNote, const string& magazine, bool want) {
    check(Solution().canConstruct(ransomNote, magazine), want, "ransomNote", ransomNote, "magazine", magazine);
}

static bool oracle(string note, string mag) {
    sort(note.begin(), note.end());
    sort(mag.begin(), mag.end());
    size_t j = 0;
    for (char c : mag) {
        if (j < note.size() && note[j] == c) {
            ++j;
        }
    }
    return j == note.size();
}

TEST(examples) {
    run("cab", "abcd", true);
    run("noon", "onion", true);
    run("aa", "ab", false);
}

TEST(edge_cases) {
    run("a", "a", true);
    run("a", "b", false);
    run("abc", "ab", false);
    run("abc", "cba", true);
    run("zz", "zaz", true);
    run("zzz", "zaz", false);
    run("hello", "ohlel", true);
    run("hello", "helo", false);
    run("b", "aaaaaaaaab", true);
    run("ab", "bbbbbbbbbb", false);
}

TEST(random) {
    Rng rng(173);
    for (int i = 0; i < 500; ++i) {
        int n = rng(1, 8), m = rng(1, 12);
        string note = rng.str(n, "abc"), mag = rng.str(m, "abcd");
        run(note, mag, oracle(note, mag));
    }
}

TEST(large) {
    Rng rng(1730);
    string mag = rng.str(100000, "abcdefghijklmnopqrstuvwxyz");
    vector<char> letters(mag.begin(), mag.end());
    rng.shuffle(letters);
    string note(letters.begin(), letters.end());
    run(note, mag, true);
    note[12345] = note[12345] == 'z' ? 'a' : note[12345] + 1;
    run(note, mag, false);
    run(string(50000, 'b') + string(50000, 'a'), string(50000, 'a') + string(50000, 'b'), true);
    run(string(100000, 'q'), string(99999, 'q') + "r", false);
    run(string(99999, 'q') + "r", "r" + string(99999, 'q'), true);
    for (int iter = 0; iter < 3; ++iter) {
        string n2 = rng.str(rng(90000, 100000), "abc"), m2 = rng.str(100000, "abc");
        run(n2, m2, oracle(n2, m2));
    }
}

}
