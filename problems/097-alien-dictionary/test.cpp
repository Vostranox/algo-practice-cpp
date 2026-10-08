#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Words = vector<string>;

static bool sorted_under(const Words& words, const string& order) {
    array<int, 128> rank{};
    for (size_t i = 0; i < order.size(); ++i) {
        rank[static_cast<unsigned char>(order[i])] = i;
    }
    auto key = [&](const string& w) {
        vector<int> k;
        for (char c : w) {
            k.push_back(rank[static_cast<unsigned char>(c)]);
        }
        return k;
    };
    for (size_t i = 0; i + 1 < words.size(); ++i) {
        if (key(words[i]) > key(words[i + 1])) return false;
    }
    return true;
}

static string letters_of(const Words& words) {
    set<char> s;
    for (auto& w : words) {
        s.insert(w.begin(), w.end());
    }
    return string(s.begin(), s.end());
}

static void run(const Words& words, bool valid) {
    Words arg = words;
    string got = Solution().alienOrder(arg);
    if (!valid) {
        check(got, "", "words", words);
        return;
    }
    string letters = letters_of(words), have = got;
    sort(have.begin(), have.end());
    ensure(have == letters, "should contain each of the letters \"" + letters + "\" exactly once", "got", got,
           "words", words);
    for (size_t i = 0; i + 1 < words.size(); ++i) {
        if (!sorted_under({words[i], words[i + 1]}, got)) {
            ensure(false, "under this order " + repr(words[i]) + " would come after " + repr(words[i + 1]), "got",
                   got, "words", words);
        }
    }
}

static bool sortable(const Words& words) {
    string order = letters_of(words);
    do {
        if (sorted_under(words, order)) return true;
    } while (next_permutation(order.begin(), order.end()));
    return false;
}

static void shuffle_letters(Rng& rng, string& s) {
    vector<char> v(s.begin(), s.end());
    rng.shuffle(v);
    s.assign(v.begin(), v.end());
}

static Words sort_by(Words words, const string& order) {
    array<int, 128> rank{};
    for (size_t i = 0; i < order.size(); ++i) {
        rank[static_cast<unsigned char>(order[i])] = i;
    }
    sort(words.begin(), words.end(), [&](const string& a, const string& b) {
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                       [&](char x, char y) { return rank[static_cast<unsigned char>(x)] < rank[static_cast<unsigned char>(y)]; });
    });
    return words;
}

TEST(examples) {
    run({"bca", "aaa", "acb"}, true);
    run({"pq", "pr", "s"}, true);
    run({"x", "z", "x"}, false);
}

TEST(edge_cases) {
    run({"z"}, true);
    run({"abc"}, true);
    run({"aaa", "aaa"}, true);
    run({"ab", "abc"}, true);
    run({"abc", "ab"}, false);
    run({"a", "b", "bc", "b"}, false);
    run({"ca", "cb", "ba"}, true);
    run({"wxyz", "wxyq"}, true);
    run({"abd", "acb", "acd"}, true);
    run({"ab", "bc", "ca", "ab"}, false);
    run({"b", "a", "ab"}, true);
    run({"ac", "ab", "zc", "zb"}, true);
}

TEST(random) {
    Rng rng(97);
    string abc = "abcde";
    for (int t = 0; t < 500; ++t) {
        string alphabet = abc.substr(0, rng(1, 5));
        Words words;
        for (int i = rng(1, 6); i > 0; --i) {
            words.push_back(rng.str(rng(1, 4), alphabet));
        }
        if (rng.coin(0.6)) {
            string order = alphabet;
            shuffle_letters(rng, order);
            words = sort_by(words, order);
            if (rng.coin(0.3)) {
                swap(words[rng(0, words.size() - 1)], words[rng(0, words.size() - 1)]);
            }
        }
        run(words, sortable(words));
    }
}

TEST(large) {
    Rng rng(970);
    string order = "abcdefghijklmnopqrstuvwxyz";
    for (int t = 0; t < 5; ++t) {
        shuffle_letters(rng, order);
        Words words;
        for (int i = 0; i < 99; ++i) {
            int len = rng(2, 100);
            string w = rng.str(len, order);
            if (rng.coin(0.5) && !words.empty()) {
                w = words[rng(0, words.size() - 1)].substr(0, rng(1, 5)) + w;
                w.resize(min<size_t>(w.size(), 100));
            }
            words.push_back(w);
        }
        words = sort_by(words, order);
        run(words, true);
        Words bad = words;
        bad.push_back(words.back().substr(0, words.back().size() - 1));
        run(bad, false);
    }
    Words singles;
    for (char c : order) {
        singles.push_back(string(1, c));
    }
    run(singles, true);
    singles.push_back(string(2, order[25]));
    singles.push_back(string{order[25], order[0]});
    run(singles, false);
}

}
