#include "prelude.hpp"

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        int m = num1.size(), n = num2.size();
        vector<int> res(m + n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res[i + j] += (num1[m - 1 - i] - '0') * (num2[n - 1 - j] - '0');
            }
        }
        for (int k = 0, carry = 0; k < m + n; ++k) {
            res[k] += carry;
            carry = res[k] / 10;
            res[k] %= 10;
        }
        while (res.size() > 1 && res.back() == 0) {
            res.pop_back();
        }
        string out;
        for (int k = res.size() - 1; k >= 0; --k) {
            out.push_back(char('0' + res[k]));
        }
        return out;
    }
};
