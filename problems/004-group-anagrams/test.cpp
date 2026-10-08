#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<string> strs, vector<vector<string>> want) {
    vector<string> arg = strs;
    vector<vector<string>> got = Solution().groupAnagrams(arg);
    check(sort_all(got), sort_all(want), "strs", strs);
}

static string sorted_str(string s) {
    sort(s.begin(), s.end());
    return s;
}

static vector<vector<string>> brute(const vector<string>& strs) {
    vector<vector<string>> groups;
    for (const string& w : strs) {
        bool placed = false;
        for (auto& g : groups) {
            if (sorted_str(g[0]) == sorted_str(w)) {
                g.push_back(w);
                placed = true;
                break;
            }
        }
        if (!placed) {
            groups.push_back({w});
        }
    }
    return groups;
}

TEST(examples) {
    run({"stop", "pots", "cat", "tops", "act", "dog"}, {{"stop", "pots", "tops"}, {"cat", "act"}, {"dog"}});
    run({"ab", "ba", "ab", "c"}, {{"ab", "ba", "ab"}, {"c"}});
    run({""}, {{""}});
}

TEST(edge_cases) {
    run({"x"}, {{"x"}});
    run({"", ""}, {{"", ""}});
    run({"", "a", ""}, {{"", ""}, {"a"}});
    run({"aab", "abb", "bab", "aba"}, {{"aab", "aba"}, {"abb", "bab"}});
    run({"ab", "abab", "ba"}, {{"ab", "ba"}, {"abab"}});
    run({"abc", "def", "ghi"}, {{"abc"}, {"def"}, {"ghi"}});
    string a1b11 = "a" + string(11, 'b'), a11b1 = string(11, 'a') + "b", b11a1 = string(11, 'b') + "a";
    run({a1b11, a11b1, b11a1}, {{a1b11, b11a1}, {a11b1}});
    run({string(100, 'z'), string(100, 'y'), string(100, 'z')}, {{string(100, 'z'), string(100, 'z')}, {string(100, 'y')}});
}

TEST(random) {
    Rng rng(4);
    for (int i = 0; i < 300; ++i) {
        vector<string> strs(rng(1, 12));
        for (auto& s : strs) {
            s = rng.str(rng(0, 4), "abc");
        }
        run(strs, brute(strs));
    }
}

TEST(large) {
    Rng rng(44);
    set<string> keys;
    while (keys.size() < 5000) {
        keys.insert(sorted_str(rng.str(rng(1, 100), "abcdefghijklmnopqrstuvwxyz")));
    }
    vector<vector<string>> want;
    vector<string> strs;
    for (const string& key : keys) {
        vector<string> group;
        for (int k = 0; k < 2; ++k) {
            vector<char> v(key.begin(), key.end());
            rng.shuffle(v);
            group.emplace_back(v.begin(), v.end());
            strs.push_back(group.back());
        }
        want.push_back(group);
    }
    rng.shuffle(strs);
    run(strs, want);
}

}
