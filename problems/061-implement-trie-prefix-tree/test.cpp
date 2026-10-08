#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

TEST(example) {
    Trace t("Trie");
    Trie trie;
    CALL(t, trie, insert, "card");
    EXPECT_CALL(t, false, trie, search, "car");
    EXPECT_CALL(t, true, trie, startsWith, "car");
    CALL(t, trie, insert, "car");
    EXPECT_CALL(t, true, trie, search, "car");
    EXPECT_CALL(t, false, trie, startsWith, "cart");
    EXPECT_CALL(t, true, trie, search, "card");
}

TEST(edge_cases) {
    Trace t("Trie");
    Trie trie;
    EXPECT_CALL(t, false, trie, search, "a");
    EXPECT_CALL(t, false, trie, startsWith, "a");
    CALL(t, trie, insert, "a");
    EXPECT_CALL(t, true, trie, search, "a");
    EXPECT_CALL(t, true, trie, startsWith, "a");
    EXPECT_CALL(t, false, trie, search, "b");
    EXPECT_CALL(t, false, trie, startsWith, "ab");
    CALL(t, trie, insert, "abc");
    EXPECT_CALL(t, false, trie, search, "ab");
    EXPECT_CALL(t, true, trie, startsWith, "ab");
    EXPECT_CALL(t, true, trie, search, "a");
    CALL(t, trie, insert, "abc");
    EXPECT_CALL(t, true, trie, search, "abc");
    EXPECT_CALL(t, false, trie, search, "abcd");
    EXPECT_CALL(t, false, trie, startsWith, "abcd");
    EXPECT_CALL(t, false, trie, startsWith, "b");
    CALL(t, trie, insert, "zzz");
    EXPECT_CALL(t, true, trie, startsWith, "zz");
    EXPECT_CALL(t, false, trie, search, "zz");
}

TEST(long_words) {
    Trace t("Trie");
    Trie trie;
    string z(2000, 'z'), y = string(1999, 'z') + "y";
    CALL(t, trie, insert, z);
    EXPECT_CALL(t, false, trie, search, z.substr(0, 1999));
    EXPECT_CALL(t, true, trie, startsWith, z.substr(0, 1999));
    EXPECT_CALL(t, true, trie, startsWith, z);
    EXPECT_CALL(t, true, trie, search, z);
    EXPECT_CALL(t, false, trie, startsWith, y);
    CALL(t, trie, insert, y);
    EXPECT_CALL(t, true, trie, search, y);
    EXPECT_CALL(t, true, trie, search, z);
    EXPECT_CALL(t, false, trie, search, "z");
}

struct Model {
    set<string> words;
    void insert(const string& w) { words.insert(w); }
    bool search(const string& w) { return words.count(w); }
    bool startsWith(const string& p) {
        auto it = words.lower_bound(p);
        return it != words.end() && it->starts_with(p);
    }
};

static void random_ops(uint64_t seed, int calls, const string& alphabet, int max_len) {
    Rng rng(seed);
    Trace t("Trie");
    Trie trie;
    Model m;
    vector<string> inserted;
    for (int i = 0; i < calls; ++i) {
        double r = rng.real();
        string s;
        if (!inserted.empty() && rng.coin(0.5)) {
            s = rng.pick(inserted);
            s = s.substr(0, rng(1, s.size()));
            if (rng.coin(0.3)) {
                s += rng.str(rng(1, 2), alphabet);
            }
        } else {
            s = rng.str(rng(1, max_len), alphabet);
        }
        if (r < 0.34) {
            m.insert(s);
            inserted.push_back(s);
            CALL(t, trie, insert, s);
        } else if (r < 0.67) {
            EXPECT_CALL(t, m.search(s), trie, search, s);
        } else {
            EXPECT_CALL(t, m.startsWith(s), trie, startsWith, s);
        }
    }
}

TEST(random) {
    for (int s = 0; s < 50; ++s) {
        random_ops(s, 300, s % 2 ? "ab" : "abc", 6);
    }
}

TEST(large) {
    random_ops(208, 30000, "abcdefghijklmnopqrstuvwxyz", 12);
}

}
