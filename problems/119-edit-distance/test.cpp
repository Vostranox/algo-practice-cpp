#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& word1, const string& word2, int want) {
    check(Solution().minDistance(word1, word2), want, "word1", word1, "word2", word2);
}

static int brute(const string& word1, const string& word2) {
    size_t limit = max(word1.size(), word2.size());
    string letters = word2;
    map<string, int> dist{{word1, 0}};
    deque<string> q{word1};
    while (!q.empty()) {
        string w = q.front();
        q.pop_front();
        if (w == word2) return dist[w];
        vector<string> next;
        for (size_t i = 0; i <= w.size(); ++i) {
            if (i < w.size()) {
                next.push_back(w.substr(0, i) + w.substr(i + 1));
            }
            for (char c : letters) {
                if (w.size() < limit) {
                    next.push_back(w.substr(0, i) + c + w.substr(i));
                }
                if (i < w.size()) {
                    next.push_back(w.substr(0, i) + c + w.substr(i + 1));
                }
            }
        }
        for (auto& v : next) {
            if (!dist.count(v)) {
                dist[v] = dist[w] + 1;
                q.push_back(v);
            }
        }
    }
    fail("unreachable");
}

static int suffix_table(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> d(n + 1, vector<int>(m + 1, 0));
    for (int i = n; i >= 0; --i) {
        for (int j = m; j >= 0; --j) {
            if (i == n || j == m) {
                d[i][j] = (n - i) + (m - j);
            } else if (a[i] == b[j]) {
                d[i][j] = d[i + 1][j + 1];
            } else {
                d[i][j] = 1 + min({d[i + 1][j], d[i][j + 1], d[i + 1][j + 1]});
            }
        }
    }
    return d[0][0];
}

TEST(examples) {
    run("kitten", "sitting", 3);
    run("flaw", "lawn", 2);
    run("", "abc", 3);
}

TEST(edge_cases) {
    run("", "", 0);
    run("same", "same", 0);
    run("a", "", 1);
    run("a", "b", 1);
    run("ab", "ba", 2);
    run("abc", "abcabc", 3);
    run("horse", "ros", 3);
    run("intention", "execution", 5);
    run("sun", "snow", 3);
}

TEST(random) {
    Rng rng(1190);
    for (int iter = 0; iter < 150; ++iter) {
        string a = rng.str(rng(0, 4), "abc"), b = rng.str(rng(0, 4), "abc");
        run(a, b, brute(a, b));
    }
}

TEST(large) {
    run(string(500, 'a'), string(500, 'b'), 500);
    run(string(500, 'a'), string(250, 'a'), 250);
    run(string(500, 'a'), "", 500);
    string ab, ba;
    for (int i = 0; i < 250; ++i) {
        ab += "ab", ba += "ba";
    }
    run(ab, ba, 2);
    Rng rng(1191);
    for (int iter = 0; iter < 3; ++iter) {
        string a = rng.str(500, "abc"), b = rng.str(rng(400, 500), "abc");
        run(a, b, suffix_table(a, b));
    }
}

}
