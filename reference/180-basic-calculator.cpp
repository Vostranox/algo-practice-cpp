#include "prelude.hpp"

class Solution {
public:
    int calculate(string s) {
        vector<pair<int, int>> saved;
        int total = 0, sign = 1;
        for (size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (isdigit(c)) {
                int num = 0;
                while (i < s.size() && isdigit(s[i])) {
                    num = num * 10 + (s[i++] - '0');
                }
                --i;
                total += sign * num;
            } else if (c == '+' || c == '-') {
                sign = c == '+' ? 1 : -1;
            } else if (c == '(') {
                saved.emplace_back(total, sign);
                total = 0, sign = 1;
            } else if (c == ')') {
                auto [outer, outer_sign] = saved.back();
                saved.pop_back();
                total = outer + outer_sign * total;
            }
        }
        return total;
    }
};
