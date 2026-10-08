#include "prelude.hpp"

class Solution {
    vector<string> res;
    string cur;

    void go(int n, int opened, int closed) {
        if (closed == n) {
            res.push_back(cur);
            return;
        }
        if (opened < n) {
            cur.push_back('(');
            go(n, opened + 1, closed);
            cur.pop_back();
        }
        if (closed < opened) {
            cur.push_back(')');
            go(n, opened, closed + 1);
            cur.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        res.clear();
        go(n, 0, 0);
        return res;
    }
};
