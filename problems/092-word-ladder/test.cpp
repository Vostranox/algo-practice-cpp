#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Words = vector<string>;

static void run(const string& begin, const string& end, const Words& words, int want) {
    Words arg = words;
    check(Solution().ladderLength(begin, end, arg), want, "beginWord", begin, "endWord", end, "wordList", words);
}

static bool one_apart(const string& a, const string& b) {
    int diff = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        diff += a[i] != b[i];
    }
    return diff == 1;
}

static int ladder(const string& begin, const string& end, const Words& words) {
    if (find(words.begin(), words.end(), end) == words.end()) return 0;
    map<string, int> dist{{begin, 1}};
    deque<string> q{begin};
    while (!q.empty()) {
        string w = q.front();
        q.pop_front();
        if (w == end) return dist[w];
        for (const string& v : words) {
            if (!dist.count(v) && one_apart(w, v)) {
                dist[v] = dist[w] + 1, q.push_back(v);
            }
        }
    }
    return 0;
}

TEST(examples) {
    run("cold", "warm", {"cord", "card", "ward", "warm", "worm", "word", "wold"}, 5);
    run("lead", "gold", {"load", "goad", "gold"}, 4);
    run("lead", "gold", {"load", "goad"}, 0);
}

TEST(edge_cases) {
    run("ab", "cb", {"cb"}, 2);
    run("a", "c", {"a", "b", "c"}, 2);
    run("hot", "dog", {"hot", "dog"}, 0);
    run("abc", "abd", {"abc", "abd"}, 2);
    run("lost", "cost", {"most", "lose", "cost"}, 2);
    run("abc", "xyz", {"xyz", "abz", "ayz"}, 4);
    run("aaa", "ccc", {"bcc", "abb", "bbb", "ccc", "bbc", "aab"}, 7);
    run("aaa", "ccc", {"abb", "bbb", "ccc", "bbc", "bcc"}, 0);
    Words stairs;
    for (char c = 'a'; c <= 'z'; ++c) {
        stairs.push_back(string{c, c});
        if (c < 'z') {
            stairs.push_back(string{c, char(c + 1)});
        }
    }
    Rng rng(920);
    rng.shuffle(stairs);
    run("aa", "zz", stairs, 51);
}

TEST(random) {
    Rng rng(92);
    for (int t = 0; t < 400; ++t) {
        int len = rng(1, 3);
        string alphabet = rng.coin() ? "abc" : "abcd";
        set<string> pool;
        int m = rng(1, 20);
        for (int i = 0; i < m; ++i) {
            pool.insert(rng.str(len, alphabet));
        }
        Words words(pool.begin(), pool.end());
        rng.shuffle(words);
        string begin = rng.str(len, alphabet), end = rng.coin(0.8) ? rng.pick(words) : rng.str(len, alphabet);
        if (begin == end) continue;
        run(begin, end, words, ladder(begin, end, words));
    }
}

TEST(large) {
    Rng rng(921);
    Words abcde, vwxyz;
    for (int i = 0; i < 3125; ++i) {
        string a, v;
        for (int x = i, k = 0; k < 5; ++k, x /= 5) {
            a += char('a' + x % 5), v += char('v' + x % 5);
        }
        abcde.push_back(a), vwxyz.push_back(v);
    }
    rng.shuffle(vwxyz);
    Words words = abcde;
    words.insert(words.end(), vwxyz.begin(), vwxyz.begin() + 1875);
    rng.shuffle(words);
    run("aaaaz", "eeeee", words, 6);
    run("abcde", "edcba", words, 5);
    run("aaaaa", vwxyz[0], words, 0);

    Words cube;
    for (int mask = 0; mask < 1024; ++mask) {
        string w;
        for (int k = 0; k < 10; ++k) {
            w += mask >> k & 1 ? 'b' : 'a';
        }
        cube.push_back(w);
    }
    set<string> extra;
    while (extra.size() < 3976) {
        extra.insert(rng.str(10, "cdefghijklmnopqrstuvwxyz"));
    }
    words = cube;
    words.insert(words.end(), extra.begin(), extra.end());
    rng.shuffle(words);
    run("aaaaaaaaaa", "bbbbbbbbbb", words, 11);
    run("abababcccc", "babababbbb", words, 0);
    run("zaaaaaaaaa", "abbbbbbbbb", words, 11);
}

}
