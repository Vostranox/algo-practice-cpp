#include "prelude.hpp"

class Solution {
    vector<vector<string>> res;
    vector<string> cur;

    static bool palindrome(const string& s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }

    void dfs(const string& s, int i) {
        if (i == static_cast<int>(s.size())) {
            res.push_back(cur);
            return;
        }
        for (int j = i; j < static_cast<int>(s.size()); ++j) {
            if (!palindrome(s, i, j)) continue;
            cur.push_back(s.substr(i, j - i + 1));
            dfs(s, j + 1);
            cur.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s) {
        dfs(s, 0);
        return res;
    }
};
