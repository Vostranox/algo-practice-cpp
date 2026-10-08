#include "prelude.hpp"

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size(), m = words.size(), L = words[0].size();
        unordered_map<string, int> id;
        vector<int> need;
        for (auto& w : words) {
            auto [it, fresh] = id.emplace(w, static_cast<int>(need.size()));
            if (fresh) {
                need.push_back(0);
            }
            ++need[it->second];
        }
        vector<int> at(n, -1);
        for (int i = 0; i + L <= n; ++i) {
            auto it = id.find(s.substr(i, L));
            if (it != id.end()) {
                at[i] = it->second;
            }
        }
        vector<int> res;
        for (int r = 0; r < L; ++r) {
            vector<int> have(need.size(), 0);
            int left = r, count = 0;
            for (int right = r; right + L <= n; right += L) {
                int w = at[right];
                if (w < 0) {
                    for (; left < right; left += L) {
                        --have[at[left]];
                    }
                    left = right + L, count = 0;
                    continue;
                }
                ++have[w], ++count;
                while (have[w] > need[w]) {
                    --have[at[left]], --count, left += L;
                }
                if (count == m) {
                    res.push_back(left);
                    --have[at[left]], --count, left += L;
                }
            }
        }
        return res;
    }
};
