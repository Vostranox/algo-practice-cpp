#include "prelude.hpp"

class Solution {
    static constexpr const char* KEYS[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string cur;

    void dfs(const string& digits, int i) {
        if (i == static_cast<int>(digits.size())) {
            res.push_back(cur);
            return;
        }
        for (const char* p = KEYS[digits[i] - '0']; *p; ++p) {
            cur.push_back(*p);
            dfs(digits, i + 1);
            cur.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        dfs(digits, 0);
        return res;
    }
};
