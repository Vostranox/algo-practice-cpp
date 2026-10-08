#include "prelude.hpp"

class Solution {
public:
    bool isValid(string s) {
        vector<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push_back(c);
            } else {
                char open = c == ')' ? '(' : c == ']' ? '[' : '{';
                if (st.empty() || st.back() != open) return false;
                st.pop_back();
            }
        }
        return st.empty();
    }
};
