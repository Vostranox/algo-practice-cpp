#include "prelude.hpp"

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        array<int, 256> to{}, from{};
        for (size_t i = 0; i < s.size(); ++i) {
            unsigned char a = s[i], b = t[i];
            if (!to[a] && !from[b]) {
                to[a] = b + 1, from[b] = a + 1;
            } else if (to[a] != b + 1 || from[b] != a + 1) {
                return false;
            }
        }
        return true;
    }
};
