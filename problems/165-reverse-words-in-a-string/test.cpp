#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const string& want) {
    check(Solution().reverseWords(s), want, "s", s);
}

static string oracle(const string& s) {
    istringstream in(s);
    vector<string> words;
    for (string w; in >> w;) {
        words.push_back(w);
    }
    string out;
    for (size_t i = words.size(); i-- > 0;) {
        out += words[i] + (i ? " " : "");
    }
    return out;
}

TEST(examples) {
    run("ready set go", "go set ready");
    run("   two  Words ", "Words two");
    run("a", "a");
}

TEST(edge_cases) {
    run("  solo  ", "solo");
    run("solo", "solo");
    run("ab cd", "cd ab");
    run("x    y", "y x");
    run(" 1 22 333 ", "333 22 1");
    run("Mixed CASE stays", "stays CASE Mixed");
    run("a b c d e", "e d c b a");
    run("ab  ab", "ab ab");
    run("palindrome emordnilap", "emordnilap palindrome");
}

TEST(random) {
    Rng rng(165);
    for (int i = 0; i < 500; ++i) {
        string s = rng.str(rng(1, 16), "aB7    ");
        if (s.find_first_not_of(' ') == string::npos) {
            s[rng(0, static_cast<int>(s.size()) - 1)] = 'Z';
        }
        run(s, oracle(s));
    }
}

TEST(large) {
    string s;
    for (int i = 0; i < 5000; ++i) {
        s += string(1, 'a' + i % 26) + " ";
    }
    run(s, oracle(s));
    run(string(9999, ' ') + "Q", "Q");
    run(string(5000, 'L') + string(4999, ' ') + "R", "R " + string(5000, 'L'));
    Rng rng(1650);
    for (int iter = 0; iter < 5; ++iter) {
        string t = rng.str(10000, "abcXYZ0123   ");
        run(t, oracle(t));
    }
}

}
