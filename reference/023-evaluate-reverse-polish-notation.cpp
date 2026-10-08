#include "prelude.hpp"

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> st;
        for (const string& t : tokens) {
            if (t.size() == 1 && string("+-*/").find(t[0]) != string::npos) {
                int b = st.back(); st.pop_back();
                int a = st.back(); st.pop_back();
                switch (t[0]) {
                    case '+': st.push_back(a + b); break;
                    case '-': st.push_back(a - b); break;
                    case '*': st.push_back(a * b); break;
                    default: st.push_back(a / b);
                }
            } else {
                st.push_back(stoi(t));
            }
        }
        return st.back();
    }
};
