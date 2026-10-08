#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& s, const string& t, const string& want) {
    check(Solution().minWindow(s, t), want, "s", s, "t", t);
}

static set<string> brute(const string& s, const string& t) {
    map<char, int> need;
    for (char c : t) {
        ++need[c];
    }
    for (size_t len = t.size(); len <= s.size(); ++len) {
        set<string> found;
        for (size_t i = 0; i + len <= s.size(); ++i) {
            map<char, int> have;
            for (size_t j = i; j < i + len; ++j) {
                ++have[s[j]];
            }
            bool ok = true;
            for (auto [c, cnt] : need) {
                ok = ok && have[c] >= cnt;
            }
            if (ok) {
                found.insert(s.substr(i, len));
            }
        }
        if (!found.empty()) return found;
    }
    return {};
}

TEST(examples) {
    run("xbyyaczabx", "abc", "czab");
    run("ayyaxa", "aa", "axa");
    run("a", "aa", "");
}

TEST(edge_cases) {
    run("a", "a", "a");
    run("a", "b", "");
    run("a", "A", "");
    run("ab", "b", "b");
    run("abc", "abcd", "");
    run("abc", "cba", "abc");
    run("bba", "ab", "ba");
    run("xAyya", "Aa", "Ayya");
    run("aab", "aab", "aab");
    run("qqrq", "qq", "qq");
    run("ADOBECODEBANCX", "ABCX", "BANCX");
    run("zzazzbzzczzzzbca", "abc", "bca");
}

TEST(random) {
    Rng rng(19);
    for (int done = 0; done < 300;) {
        string s = rng.str(rng(1, 10), "abA"), t = rng.str(rng(1, 3), "abA");
        set<string> windows = brute(s, t);
        if (windows.size() <= 1) {
            run(s, t, windows.empty() ? "" : *windows.begin());
            ++done;
        }
    }
}

TEST(large) {
    Rng rng(1919);
    const int n = 100000;
    string s = "x" + string(n - 2, 'a') + "y";
    run(s, "yx", s);
    s = string(50000, 'a') + "b" + string(49999, 'c');
    run(s, string(50000, 'a') + "b", s.substr(0, 50001));
    s = rng.str(n, "abcdefghijklm");
    s[40000] = 'Z';
    s[40500] = 'Y';
    s[41000] = 'X';
    run(s, "XYZ", s.substr(40000, 1001));
    run(s, "abcz", "");
    string ab;
    for (int i = 0; i < n / 2; ++i) {
        ab += "ab";
    }
    run(ab, string(50001, 'a'), "");
}

}
