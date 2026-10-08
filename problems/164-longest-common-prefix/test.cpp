#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<string> strs, const string& want) {
    vector<string> arg = strs;
    check(Solution().longestCommonPrefix(arg), want, "strs", strs);
}

static string oracle(const vector<string>& strs) {
    string shortest = *min_element(strs.begin(), strs.end(), [](auto& a, auto& b) { return a.size() < b.size(); });
    for (size_t len = shortest.size();; --len) {
        string p = shortest.substr(0, len);
        if (all_of(strs.begin(), strs.end(), [&](const string& s) { return s.compare(0, len, p) == 0; })) return p;
    }
}

TEST(examples) {
    run({"interview", "internet", "interval"}, "inter");
    run({"car", "cat", "dog"}, "");
    run({"ab", "abc", "abcd"}, "ab");
}

TEST(edge_cases) {
    run({"alone"}, "alone");
    run({""}, "");
    run({"abc", ""}, "");
    run({"", "abc"}, "");
    run({"abcd", "abc", "ab"}, "ab");
    run({"same", "same", "same"}, "same");
    run({"a", "b"}, "");
    run({"prefix", "prefix", "prefiz"}, "prefi");
    run({"xa", "ya"}, "");
    run({"reflow", "reflex", "refine"}, "ref");
}

TEST(random) {
    Rng rng(164);
    for (int i = 0; i < 500; ++i) {
        string base = rng.str(rng(0, 6), "ab");
        vector<string> strs(rng(1, 5));
        for (auto& s : strs) {
            s = base.substr(0, rng(0, static_cast<int>(base.size())));
            s += rng.str(rng(0, 3), "ab");
        }
        run(strs, oracle(strs));
    }
}

TEST(large) {
    vector<string> strs(200, string(200, 'k'));
    run(strs, string(200, 'k'));
    strs[199][199] = 'j';
    run(strs, string(199, 'k'));
    strs[100].pop_back();
    strs[100].pop_back();
    run(strs, string(198, 'k'));
    strs[0][0] = 'a';
    run(strs, "");
    Rng rng(1640);
    string base = rng.str(200, "abcdefghijklmnopqrstuvwxyz");
    for (int iter = 0; iter < 5; ++iter) {
        vector<string> v(200, base);
        for (int j = 0; j < 3; ++j) {
            string& w = v[rng(0, 199)];
            int pos = rng(100, 199);
            if (rng.coin()) {
                w.resize(min(w.size(), static_cast<size_t>(pos)));
            } else if (pos < static_cast<int>(w.size())) {
                w[pos] = w[pos] == 'z' ? 'a' : w[pos] + 1;
            }
        }
        run(v, oracle(v));
    }
}

}
