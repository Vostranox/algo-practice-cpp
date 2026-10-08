#include "prelude.hpp"

class Codec {
public:
    string encode(vector<string>& strs) {
        string out;
        for (const string& s : strs) {
            out += to_string(s.size()) + "#" + s;
        }
        return out;
    }

    vector<string> decode(string s) {
        vector<string> res;
        size_t i = 0;
        while (i < s.size()) {
            size_t j = s.find('#', i);
            size_t len = stoul(s.substr(i, j - i));
            res.push_back(s.substr(j + 1, len));
            i = j + 1 + len;
        }
        return res;
    }
};
