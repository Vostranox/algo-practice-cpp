#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& pattern, const string& s, bool want) {
    check(Solution().wordPattern(pattern, s), want, "pattern", pattern, "s", s);
}

static vector<string> split(const string& s) {
    vector<string> words;
    size_t start = 0;
    for (size_t sp; (sp = s.find(' ', start)) != string::npos; start = sp + 1) {
        words.push_back(s.substr(start, sp - start));
    }
    words.push_back(s.substr(start));
    return words;
}

template <class Seq>
static vector<int> shape(const Seq& items) {
    vector<int> out;
    for (size_t i = 0; i < items.size(); ++i) {
        out.push_back(find(items.begin(), items.end(), items[i]) - items.begin());
    }
    return out;
}

static bool oracle(const string& pattern, const string& s) { return shape(pattern) == shape(split(s)); }

static string join(const vector<string>& words) {
    string s;
    for (size_t i = 0; i < words.size(); ++i) {
        s += (i ? " " : "") + words[i];
    }
    return s;
}

TEST(examples) {
    run("xyyx", "red blue blue red", true);
    run("xyyx", "red blue blue blue", false);
    run("xy", "sun sun", false);
}

TEST(edge_cases) {
    run("a", "word", true);
    run("aa", "go go", true);
    run("ab", "go go", false);
    run("aa", "go stop", false);
    run("abc", "one two", false);
    run("ab", "one two three", false);
    run("aaa", "on on on on", false);
    run("aaaa", "on on on one", false);
    run("ab", "a aa", true);
    run("abc", "c a b", true);
    run("aba", "x y x", true);
    run("aba", "x y y", false);
    run("abab", "q w q w", true);
}

TEST(random) {
    Rng rng(175);
    vector<string> vocab = {"x", "y", "xy", "yx", "xx"};
    for (int i = 0; i < 500; ++i) {
        string pattern = rng.str(rng(1, 6), "abc");
        vector<string> words;
        if (rng.coin()) {
            vector<string> image = {rng.pick(vocab), rng.pick(vocab), rng.pick(vocab)};
            for (char c : pattern) {
                words.push_back(image[c - 'a']);
            }
        } else {
            for (size_t j = 0; j < pattern.size(); ++j) {
                words.push_back(rng.pick(vocab));
            }
        }
        if (rng.coin(0.15)) {
            words.push_back(rng.pick(vocab));
        } else if (rng.coin(0.15) && words.size() > 1) {
            words.pop_back();
        }
        string s = join(words);
        run(pattern, s, oracle(pattern, s));
    }
}

TEST(large) {
    Rng rng(1750);
    set<string> distinct;
    while (distinct.size() < 26) {
        distinct.insert(rng.str(9, "abcdefghijklmnopqrstuvwxyz"));
    }
    vector<string> word_of(distinct.begin(), distinct.end());
    rng.shuffle(word_of);
    string pattern = rng.str(300, "abcdefghijklmnopqrstuvwxyz");
    vector<string> words;
    for (char c : pattern) {
        words.push_back(word_of[c - 'a']);
    }
    run(pattern, join(words), true);
    vector<string> changed = words;
    char other = pattern.back() == 'z' ? 'a' : pattern.back() + 1;
    changed.back() = word_of[other - 'a'];
    run(pattern, join(changed), false);
    changed = words;
    changed.pop_back();
    run(pattern, join(changed), false);
    run(string(300, 'k'), join(vector<string>(300, word_of[0])), true);
    changed = vector<string>(300, word_of[0]);
    changed[299] = word_of[1];
    run(string(300, 'k'), join(changed), false);
    run(pattern, join(vector<string>(300, word_of[0])), false);
}

}
