#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, vector<string> words, bool want) {
    vector<string> arg = words;
    check(Solution().wordBreak(s, arg), want, "s", s, "wordDict", words);
}

static bool brute(const string& s, const vector<string>& words, size_t pos = 0) {
    if (pos == s.size()) return true;
    for (auto& w : words) {
        if (s.compare(pos, w.size(), w) == 0 && brute(s, words, pos + w.size())) return true;
    }
    return false;
}

static bool reachable_end(const string& s, const vector<string>& words) {
    vector<bool> seen(s.size() + 1, false);
    vector<size_t> stack{0};
    seen[0] = true;
    while (!stack.empty()) {
        size_t i = stack.back();
        stack.pop_back();
        for (auto& w : words) {
            size_t j = i + w.size();
            if (j <= s.size() && !seen[j] && s.compare(i, w.size(), w) == 0) {
                seen[j] = true;
                stack.push_back(j);
            }
        }
    }
    return seen[s.size()];
}

static vector<string> random_words(Rng& rng, const string& letters, size_t count, int lo, int hi) {
    set<string> out;
    while (out.size() < count) {
        out.insert(rng.str(rng(lo, hi), letters));
    }
    return vector<string>(out.begin(), out.end());
}

TEST(examples) {
    run("sunflower", {"sun", "flower", "flow"}, true);
    run("abab", {"ab"}, true);
    run("carpet", {"car", "pe", "pets"}, false);
}

TEST(edge_cases) {
    run("a", {"a"}, true);
    run("a", {"b"}, false);
    run("aaaaaaa", {"aaaa", "aaa"}, true);
    run("aaaaaaa", {"aaaa", "aa"}, false);
    run("cars", {"car", "ca", "rs"}, true);
    run("goalspecial", {"go", "goal", "goals", "special"}, true);
    run("abcd", {"a", "abc", "b", "cd"}, true);
    run("ab", {"abc"}, false);
    run("dogs", {"dog", "s", "gs"}, true);
}

TEST(random) {
    Rng rng(1080);
    for (int iter = 0; iter < 300; ++iter) {
        vector<string> words = random_words(rng, "ab", rng(1, 4), 1, 4);
        string s = rng.str(rng(1, 12), "ab");
        run(s, words, brute(s, words));
    }
}

TEST(large) {
    Rng rng(1081);
    vector<string> aWords;
    for (int k = 1; k <= 20; ++k) {
        aWords.push_back(string(k, 'a'));
    }
    vector<string> others = random_words(rng, "cdefgh", 980, 1, 20);
    vector<string> dict = aWords;
    dict.insert(dict.end(), others.begin(), others.end());
    run(string(299, 'a') + "b", dict, false);
    reverse(dict.begin(), dict.end());
    run(string(300, 'a'), dict, true);
    vector<string> withAb(aWords.begin() + 1, aWords.end());
    withAb.push_back("ab");
    run(string(299, 'a') + "b", withAb, true);
    for (int iter = 0; iter < 4; ++iter) {
        vector<string> words = random_words(rng, "ab", 30, 3, 8);
        string s;
        while (s.size() < 300) {
            s += rng.pick(words);
        }
        s.resize(300);
        if (rng.coin()) {
            int i = rng(0, 299);
            s[i] = s[i] == 'a' ? 'b' : 'a';
        }
        run(s, words, reachable_end(s, words));
    }
}

}
