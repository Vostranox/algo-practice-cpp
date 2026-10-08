#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(string s, vector<vector<string>> want) {
    auto got = sorted(Solution().partition(s));
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the partition " + repr(*d) + " appears more than once", "s", s, "got", got);
    }
    check(got, sorted(want), "s", s);
}

static bool is_pal(const string& s, size_t i, size_t j) {
    while (i + 1 < j) {
        if (s[i++] != s[--j]) return false;
    }
    return true;
}

static vector<vector<string>> oracle(const string& s) {
    vector<vector<string>> out;
    for (int mask = 0; mask < (1 << (s.size() - 1)); ++mask) {
        vector<size_t> cuts = {0};
        for (size_t gap = 1; gap < s.size(); ++gap) {
            if (mask >> (gap - 1) & 1) {
                cuts.push_back(gap);
            }
        }
        cuts.push_back(s.size());
        bool ok = true;
        for (size_t i = 0; ok && i + 1 < cuts.size(); ++i) {
            ok = is_pal(s, cuts[i], cuts[i + 1]);
        }
        if (!ok) continue;
        out.emplace_back();
        for (size_t i = 0; i + 1 < cuts.size(); ++i) {
            out.back().push_back(s.substr(cuts[i], cuts[i + 1] - cuts[i]));
        }
    }
    return out;
}

static void run_count(const string& s, size_t count) {
    auto got = Solution().partition(s);
    for (auto& parts : got) {
        string joined;
        bool pal = true;
        for (auto& p : parts) {
            joined += p, pal &= !p.empty() && is_pal(p, 0, p.size());
        }
        ensure(joined == s, "the pieces of a partition must join back to s", "s", s, "partition", parts);
        ensure(pal, "every piece must be a non-empty palindrome", "s", s, "partition", parts);
    }
    got = sorted(got);
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "the partition " + repr(*d) + " appears more than once", "s", s);
    }
    ensure(got.size() == count, "expected " + to_string(count) + " partitions, got " + to_string(got.size()), "s", s);
}

TEST(examples) {
    run("abb", {{"a", "b", "b"}, {"a", "bb"}});
    run("noon", {{"n", "o", "o", "n"}, {"n", "oo", "n"}, {"noon"}});
    run("z", {{"z"}});
}

TEST(edge_cases) {
    run("ab", {{"a", "b"}});
    run("aa", {{"a", "a"}, {"aa"}});
    run("aba", {{"a", "b", "a"}, {"aba"}});
    run("abc", {{"a", "b", "c"}});
    run("aaa", {{"a", "a", "a"}, {"a", "aa"}, {"aa", "a"}, {"aaa"}});
    run("racecar", oracle("racecar"));
    vector<string> singles;
    for (char c : string("abcdefghijklmnop")) {
        singles.push_back(string(1, c));
    }
    run("abcdefghijklmnop", {singles});
}

TEST(random) {
    Rng rng(131);
    for (int iter = 0; iter < 300; ++iter) {
        string s = rng.str(rng(1, 10), rng.coin(0.7) ? "ab" : "abc");
        run(s, oracle(s));
    }
}

TEST(large) {
    run_count(string(16, 'a'), 1 << 15);
    run("abaababaabaababa", oracle("abaababaabaababa"));
}

}
