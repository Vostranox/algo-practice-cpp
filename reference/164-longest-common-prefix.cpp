#include "prelude.hpp"

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        for (size_t i = 0; i < strs[0].size(); ++i) {
            for (const string& s : strs) {
                if (i == s.size() || s[i] != strs[0][i]) return strs[0].substr(0, i);
            }
        }
        return strs[0];
    }
};
