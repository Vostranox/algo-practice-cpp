#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(string s, vector<int> want) {
    check(Solution().partitionLabels(s), want, "s", s);
}

static vector<int> brute(const string& s) {
    int n = static_cast<int>(s.size());
    vector<int> cuts = {0};
    for (int k = 1; k < n; ++k) {
        set<char> left(s.begin(), s.begin() + k), right(s.begin() + k, s.end());
        bool shared = false;
        for (char c : left) {
            shared |= right.count(c) > 0;
        }
        if (!shared) {
            cuts.push_back(k);
        }
    }
    cuts.push_back(n);
    vector<int> sizes;
    for (size_t i = 1; i < cuts.size(); ++i) {
        sizes.push_back(cuts[i] - cuts[i - 1]);
    }
    return sizes;
}

TEST(examples) {
    run("abcbaxyzyq", {5, 1, 3, 1});
    run("abcdabef", {6, 1, 1});
    run("aaaa", {4});
}

TEST(edge_cases) {
    run("a", {1});
    run("ab", {1, 1});
    run("abba", {4});
    run("abab", {4});
    run("aabbcc", {2, 2, 2});
    run("abcdefghijklmnopqrstuvwxyz", vector<int>(26, 1));
    run("zabcz", {5});
    run("abcabcxyx", {6, 3});
    run("abacbdeffe", {5, 1, 4});
    run(string(500, 'q'), {500});
}

TEST(random) {
    Rng rng(763);
    for (int it = 0; it < 400; ++it) {
        string letters = string("abcdefghij").substr(0, rng(1, 10));
        string s = rng.str(rng(1, 15), letters);
        run(s, brute(s));
    }
}

TEST(max_length) {
    string s;
    for (char c = 'a'; c <= 'z'; ++c) {
        s += string(19, c);
    }
    run(s + "zzzzzz", [] { vector<int> v(25, 19); v.push_back(25); return v; }());
    string ab;
    for (int i = 0; i < 250; ++i) {
        ab += "ab";
    }
    run(ab, {500});
    Rng rng(5);
    for (int k : {3, 8, 26}) {
        s = rng.str(500, string("abcdefghijklmnopqrstuvwxyz").substr(0, k));
        run(s, brute(s));
    }
    s.clear();
    for (int i = 0; i < 26; i += 2) {
        s += rng.str(38, string(1, static_cast<char>('a' + i)) + static_cast<char>('a' + i + 1));
    }
    run(s, brute(s));
}

}
