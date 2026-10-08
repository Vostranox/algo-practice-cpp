#include "prelude.hpp"

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        array<int, 26> count{};
        for (char c : magazine) {
            ++count[c - 'a'];
        }
        for (char c : ransomNote) {
            if (--count[c - 'a'] < 0) return false;
        }
        return true;
    }
};
