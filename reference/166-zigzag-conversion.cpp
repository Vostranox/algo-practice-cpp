#include "prelude.hpp"

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        vector<string> rows(min(numRows, static_cast<int>(s.size())));
        int row = 0, dir = 1;
        for (char c : s) {
            rows[row] += c;
            if (row == 0) {
                dir = 1;
            } else if (row == numRows - 1) {
                dir = -1;
            }
            row += dir;
        }
        string out;
        for (const string& r : rows) {
            out += r;
        }
        return out;
    }
};
