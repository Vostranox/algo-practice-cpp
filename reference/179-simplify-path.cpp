#include "prelude.hpp"

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> dirs;
        for (size_t i = 0; i < path.size();) {
            size_t j = path.find('/', i);
            if (j == string::npos) {
                j = path.size();
            }
            string name = path.substr(i, j - i);
            if (name == "..") {
                if (!dirs.empty()) {
                    dirs.pop_back();
                }
            } else if (!name.empty() && name != ".") {
                dirs.push_back(name);
            }
            i = j + 1;
        }
        string res;
        for (auto& d : dirs) {
            res += "/" + d;
        }
        return res.empty() ? "/" : res;
    }
};
