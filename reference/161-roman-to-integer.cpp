#include "prelude.hpp"

class Solution {
public:
    int romanToInt(string s) {
        auto val = [](char c) {
            switch (c) {
                case 'I': return 1;
                case 'V': return 5;
                case 'X': return 10;
                case 'L': return 50;
                case 'C': return 100;
                case 'D': return 500;
                default: return 1000;
            }
        };
        int total = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            int v = val(s[i]);
            total += i + 1 < s.size() && v < val(s[i + 1]) ? -v : v;
        }
        return total;
    }
};
