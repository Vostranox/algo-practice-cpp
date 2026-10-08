#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s1, const string& s2, const string& s3, bool want) {
    check(Solution().isInterleave(s1, s2, s3), want, "s1", s1, "s2", s2, "s3", s3);
}

static bool brute(const string& s1, const string& s2, const string& s3) {
    int n = s3.size();
    if (s1.size() + s2.size() != s3.size()) return false;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) != static_cast<int>(s1.size())) continue;
        string a, b;
        for (int i = 0; i < n; ++i) {
            (mask >> i & 1 ? a : b) += s3[i];
        }
        if (a == s1 && b == s2) return true;
    }
    return false;
}

static bool bfs(const string& s1, const string& s2, const string& s3) {
    int n = s1.size(), m = s2.size();
    if (n + m != static_cast<int>(s3.size())) return false;
    vector<vector<bool>> seen(n + 1, vector<bool>(m + 1, false));
    deque<pair<int, int>> q{{0, 0}};
    seen[0][0] = true;
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop_front();
        if (i == n && j == m) return true;
        if (i < n && s1[i] == s3[i + j] && !seen[i + 1][j]) {
            seen[i + 1][j] = true, q.push_back({i + 1, j});
        }
        if (j < m && s2[j] == s3[i + j] && !seen[i][j + 1]) {
            seen[i][j + 1] = true, q.push_back({i, j + 1});
        }
    }
    return false;
}

static string shuffle_in(Rng& rng, const string& a, const string& b) {
    string out;
    size_t i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        out += (j == b.size() || (i < a.size() && rng.coin())) ? a[i++] : b[j++];
    }
    return out;
}

TEST(examples) {
    run("abc", "xy", "axbyc", true);
    run("ab", "cd", "adcb", false);
    run("aa", "ab", "abaa", true);
}

TEST(edge_cases) {
    run("", "", "", true);
    run("", "abc", "abc", true);
    run("", "abc", "acb", false);
    run("a", "", "", false);
    run("", "", "a", false);
    run("a", "b", "abb", false);
    run("ab", "c", "ab", false);
    run("aabcc", "dbbca", "aadbbcbcac", true);
    run("aabcc", "dbbca", "aadbbbaccc", false);
    run("ab", "ab", "abab", true);
    run("ab", "ab", "aabb", true);
    run("ab", "ab", "abba", false);
}

TEST(random) {
    Rng rng(1160);
    for (int iter = 0; iter < 400; ++iter) {
        string s1 = rng.str(rng(0, 5), "ab"), s2 = rng.str(rng(0, 5), "ab");
        string s3 = rng.coin() ? shuffle_in(rng, s1, s2) : rng.str(rng(0, 11), "ab");
        if (rng.coin(0.3) && !s3.empty()) {
            s3[rng(0, s3.size() - 1)] ^= 'a' ^ 'b';
        }
        run(s1, s2, s3, brute(s1, s2, s3));
    }
}

TEST(large) {
    string a100(100, 'a');
    run(a100, a100, string(199, 'a') + "b", false);
    run(a100, string(99, 'a') + "b", string(199, 'a') + "b", true);
    run(string(99, 'a') + "b", a100, string(199, 'a') + "b", true);
    run(a100, a100, string(201, 'a'), false);
    Rng rng(1161);
    for (int iter = 0; iter < 6; ++iter) {
        string s1 = rng.str(100, "ab"), s2 = rng.str(100, "ab");
        string s3 = shuffle_in(rng, s1, s2);
        if (iter % 2) {
            int i = rng(0, 198);
            while (s3[i] == s3[i + 1]) {
                i = rng(0, 198);
            }
            swap(s3[i], s3[i + 1]);
        }
        run(s1, s2, s3, bfs(s1, s2, s3));
    }
}

}
