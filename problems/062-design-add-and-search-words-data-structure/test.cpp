#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

TEST(example) {
    Trace t("WordDictionary");
    WordDictionary d;
    CALL(t, d, addWord, "lamp");
    CALL(t, d, addWord, "limp");
    CALL(t, d, addWord, "lamb");
    EXPECT_CALL(t, false, d, search, "lump");
    EXPECT_CALL(t, true, d, search, "l.mp");
    EXPECT_CALL(t, true, d, search, "..mb");
    EXPECT_CALL(t, false, d, search, "lam");
    EXPECT_CALL(t, true, d, search, "l..p");
    EXPECT_CALL(t, false, d, search, "lamp.");
}

TEST(edge_cases) {
    Trace t("WordDictionary");
    WordDictionary d;
    EXPECT_CALL(t, false, d, search, ".");
    EXPECT_CALL(t, false, d, search, "a");
    CALL(t, d, addWord, "ab");
    EXPECT_CALL(t, false, d, search, "a");
    EXPECT_CALL(t, false, d, search, ".");
    EXPECT_CALL(t, true, d, search, "a.");
    EXPECT_CALL(t, true, d, search, "..");
    EXPECT_CALL(t, false, d, search, "...");
    EXPECT_CALL(t, false, d, search, "abc");
    CALL(t, d, addWord, "x");
    EXPECT_CALL(t, true, d, search, ".");
    EXPECT_CALL(t, true, d, search, "x");
    EXPECT_CALL(t, false, d, search, "x.");
    CALL(t, d, addWord, "bad");
    CALL(t, d, addWord, "dad");
    CALL(t, d, addWord, "mad");
    EXPECT_CALL(t, false, d, search, "pad");
    EXPECT_CALL(t, true, d, search, "bad");
    EXPECT_CALL(t, true, d, search, ".ad");
    EXPECT_CALL(t, true, d, search, "b..");
    EXPECT_CALL(t, false, d, search, "b.b");
    EXPECT_CALL(t, true, d, search, "..d");
    EXPECT_CALL(t, false, d, search, "..e");
    CALL(t, d, addWord, "abcdefghijklmnopqrstuvwxy");
    EXPECT_CALL(t, true, d, search, "abcdefghijklmnopqrstuvwx.");
    EXPECT_CALL(t, true, d, search, ".bcdefghijklmnopqrstuvwx.");
    EXPECT_CALL(t, false, d, search, "abcdefghijklmnopqrstuvwx");
}

static bool matches(const string& pattern, const string& w) {
    if (pattern.size() != w.size()) return false;
    for (size_t i = 0; i < w.size(); ++i) {
        if (pattern[i] != '.' && pattern[i] != w[i]) return false;
    }
    return true;
}

static string with_dots(Rng& rng, string s, int dots) {
    for (int i = 0; i < dots; ++i) {
        s[rng(0, s.size() - 1)] = '.';
    }
    return s;
}

TEST(random) {
    for (int seed = 0; seed < 40; ++seed) {
        Rng rng(seed);
        string alpha = seed % 2 ? "ab" : "abc";
        Trace t("WordDictionary");
        WordDictionary d;
        vector<string> words;
        for (int i = 0; i < 250; ++i) {
            if (words.empty() || rng.coin(0.4)) {
                string w = rng.str(rng(1, 5), alpha);
                words.push_back(w);
                CALL(t, d, addWord, w);
            } else {
                string q = with_dots(rng, rng.coin() ? rng.pick(words) : rng.str(rng(1, 5), alpha), rng(0, 2));
                bool want = any_of(words.begin(), words.end(), [&](auto& w) { return matches(q, w); });
                EXPECT_CALL(t, want, d, search, q);
            }
        }
    }
}

TEST(large) {
    Rng rng(211);
    const string stored = "abcdefghijklmnopqrst", unused = "uvwxyz";
    Trace t("WordDictionary");
    WordDictionary d;
    vector<string> words;
    unordered_set<string> word_set;
    for (int i = 0; i < 5000; ++i) {
        string w = rng.str(rng(1, 25), stored);
        words.push_back(w);
        word_set.insert(w);
        CALL(t, d, addWord, w);
    }
    for (int i = 0; i < 5000; ++i) {
        string w = rng.pick(words);
        double r = rng.real();
        if (r < 0.35) {
            EXPECT_CALL(t, true, d, search, with_dots(rng, w, rng(1, 2)));
        } else if (r < 0.7) {
            string q = w;
            int pos = rng(0, q.size() - 1);
            q[pos] = unused[rng(0, unused.size() - 1)];
            for (int k = rng(0, 2); k > 0; --k) {
                int j = rng(0, q.size() - 1);
                if (j != pos) {
                    q[j] = '.';
                }
            }
            EXPECT_CALL(t, false, d, search, q);
        } else {
            string q = rng.coin() ? w : rng.str(rng(1, 4), stored);
            EXPECT_CALL(t, static_cast<bool>(word_set.count(q)), d, search, q);
        }
    }
}

}
