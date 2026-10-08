#include "prelude.hpp"

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> lines;
        int n = words.size();
        for (int i = 0; i < n;) {
            int j = i, letters = 0;
            while (j < n && letters + static_cast<int>(words[j].size()) + (j - i) <= maxWidth) {
                letters += words[j++].size();
            }
            int gaps = j - i - 1;
            string line = words[i];
            if (j == n || gaps == 0) {
                for (int k = i + 1; k < j; ++k) {
                    line += " " + words[k];
                }
                line += string(maxWidth - line.size(), ' ');
            } else {
                int spaces = maxWidth - letters, base = spaces / gaps, extra = spaces % gaps;
                for (int k = i + 1; k < j; ++k) {
                    line += string(base + (k - i <= extra), ' ') + words[k];
                }
            }
            lines.push_back(line);
            i = j;
        }
        return lines;
    }
};
