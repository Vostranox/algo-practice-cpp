#include "prelude.hpp"

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words;
        istringstream in(s);
        for (string w; in >> w;) {
            words.push_back(w);
        }
        if (words.size() != pattern.size()) return false;
        unordered_map<char, string> word_of;
        unordered_map<string, char> letter_of;
        for (size_t i = 0; i < words.size(); ++i) {
            auto word = word_of.emplace(pattern[i], words[i]).first;
            auto letter = letter_of.emplace(words[i], pattern[i]).first;
            if (word->second != words[i] || letter->second != pattern[i]) return false;
        }
        return true;
    }
};
