#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const vector<string>& words, const vector<int>& want) {
    vector<string> arg = words;
    check(sorted(Solution().findSubstring(s, arg)), sorted(want), "s", s, "words", words);
}

static vector<int> brute(const string& s, vector<string> words) {
    sort(words.begin(), words.end());
    set<string> concat;
    do {
        string c;
        for (auto& w : words) {
            c += w;
        }
        concat.insert(c);
    } while (next_permutation(words.begin(), words.end()));
    size_t len = concat.begin()->size();
    vector<int> out;
    for (size_t i = 0; i + len <= s.size(); ++i) {
        if (concat.count(s.substr(i, len))) {
            out.push_back(i);
        }
    }
    return out;
}

static vector<int> by_counting(const string& s, const vector<string>& words) {
    int n = s.size(), m = words.size(), L = words[0].size();
    map<string, int> index;
    for (auto& w : words) {
        index.emplace(w, static_cast<int>(index.size()));
    }
    vector<int> need(index.size(), 0);
    for (auto& w : words) {
        ++need[index[w]];
    }
    vector<int> id(n, -1);
    for (int i = 0; i + L <= n; ++i) {
        auto it = index.find(s.substr(i, L));
        if (it != index.end()) {
            id[i] = it->second;
        }
    }
    vector<int> out;
    for (int i = 0; i + static_cast<int64_t>(m) * L <= n; ++i) {
        vector<int> seen(need.size(), 0);
        bool ok = true;
        for (int j = 0; j < m && ok; ++j) {
            int w = id[i + j * L];
            ok = w >= 0 && ++seen[w] <= need[w];
        }
        if (ok) {
            out.push_back(i);
        }
    }
    return out;
}

static vector<int> range(int from, int to, int step = 1) {
    vector<int> out;
    for (int i = from; i <= to; i += step) {
        out.push_back(i);
    }
    return out;
}

TEST(examples) {
    run("dogcatcatdog", {"cat", "dog"}, {0, 6});
    run("xyxyxy", {"xy", "xy"}, {0, 2});
    run("zabbaz", {"ab", "ba"}, {1});
}

TEST(edge_cases) {
    run("a", {"a"}, {0});
    run("a", {"b"}, {});
    run("ab", {"abc"}, {});
    run("abc", {"a", "b", "c", "d"}, {});
    run("aaa", {"a", "a"}, {0, 1});
    run("aaa", {"a", "a", "a", "a"}, {});
    run("abcabc", {"abc"}, {0, 3});
    run("abcabc", {"bca"}, {1});
    run("abab", {"ab", "ab"}, {0});
    run("ababa", {"ab", "ba"}, {});
    run("aabbaabb", {"a", "a", "b", "b"}, {0, 1, 2, 3, 4});
    run("ababxabab", {"ab", "ab"}, {0, 5});
    run("foofoobarfoo", {"foo", "bar"}, {3, 6});
    run("foofoobarfoo", {"foo", "foo", "bar"}, {0, 3});
    run("catcatdogcat", {"cat", "dog"}, {3, 6});
    run("xyzabcxyzabc", {"abc", "xyz"}, {0, 3, 6});
}

TEST(random) {
    Rng rng(30);
    for (int it = 0; it < 1500; ++it) {
        int L = rng(1, 3), m = rng(1, 4);
        vector<string> words(m);
        for (auto& w : words) {
            w = rng.str(L, "ab");
        }
        string s = rng.str(rng(0, 6), "ab");
        if (rng.coin(0.7)) {
            vector<string> order = words;
            rng.shuffle(order);
            for (auto& w : order) {
                s += w;
            }
            if (rng.coin(0.3)) {
                s.back() = s.back() == 'a' ? 'b' : 'a';
            }
        }
        s += rng.str(rng(s.empty() ? 1 : 0, 6), "ab");
        run(s, words, brute(s, words));
    }
}

static vector<string> words_of(int count, const string& a, int count2 = 0, const string& b = "") {
    vector<string> out(count, a);
    out.insert(out.end(), count2, b);
    return out;
}

const string a10k(10000, 'a');

static string ab5k() {
    string ab;
    for (int i = 0; i < 5000; ++i) {
        ab += "ab";
    }
    return ab;
}

TEST(large) {
    run(a10k, words_of(333, string(30, 'a')), range(0, 10));
    run(a10k, words_of(5000, string(30, 'a')), {});
    run(ab5k(), words_of(2500, "ab"), range(0, 5000, 2));
    run(ab5k(), words_of(2500, "ba"), range(1, 4999, 2));
}

TEST(large_many_words) {
    string ab = ab5k();
    run(a10k, words_of(5000, "a"), range(0, 5000));
    run(ab, words_of(2500, "a", 2500, "b"), range(0, 5000));
    run(a10k, words_of(4999, "a", 1, "b"), {});
    run(ab, words_of(2501, "a", 2499, "b"), {});
    run(string(9999, 'a') + "b", words_of(4999, "a", 1, "b"), {5000});
    run("b" + string(9999, 'a'), words_of(4999, "a", 1, "b"), {0});
    run(a10k, words_of(2500, "aa"), range(0, 5000));
    string abc;
    for (int i = 0; i < 3333; ++i) {
        abc += "abc";
    }
    abc += "a";
    vector<string> words = words_of(1667, "a", 1667, "b");
    words.insert(words.end(), 1666, "c");
    run(abc, words, range(0, 4998, 3));
}

TEST(large_random) {
    Rng rng(3030);
    vector<string> three = {rng.str(30, "ab"), rng.str(30, "ab"), rng.str(30, "ab")};
    vector<string> words;
    for (int i = 0; i < 300; ++i) {
        words.push_back(three[i % 3]);
    }
    string s;
    for (int i = 0; i < 333; ++i) {
        s += three[i % 3];
    }
    s += "ab";
    run(s, words, by_counting(s, words));
    s.replace(30 * 200, 30, three[0]);
    run(s, words, by_counting(s, words));
    set<string> distinct;
    while (distinct.size() < 3333) {
        distinct.insert(rng.str(3, "abcdefghijklmnopqrstuvwxyz"));
    }
    words.assign(distinct.begin(), distinct.end());
    rng.shuffle(words);
    s = "q";
    for (auto& w : words) {
        s += w;
    }
    run(s, words, by_counting(s, words));
    words.clear();
    for (int i = 0; i < 5000; ++i) {
        words.push_back(rng.str(2, "ab"));
    }
    vector<string> order = words;
    rng.shuffle(order);
    s.clear();
    for (auto& w : order) {
        s += w;
    }
    run(s, words, {0});
    for (int flips = 1; flips <= 3; ++flips) {
        s[rng(0, 9999)] ^= 'a' ^ 'b';
        run(s, words, by_counting(s, words));
    }
    words.resize(1000);
    s.clear();
    for (int k = 0; k < 5; ++k) {
        order = words;
        rng.shuffle(order);
        for (auto& w : order) {
            s += w;
        }
    }
    run(s, words, by_counting(s, words));
}

}
