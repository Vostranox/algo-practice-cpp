#include "prelude.hpp"

class Solution {
public:
    string alienOrder(vector<string>& words) {
        map<char, set<char>> after;
        map<char, int> indegree;
        for (auto& w : words) {
            for (char c : w) {
                indegree.emplace(c, 0);
            }
        }
        for (size_t i = 0; i + 1 < words.size(); ++i) {
            const string &a = words[i], &b = words[i + 1];
            size_t j = 0;
            while (j < a.size() && j < b.size() && a[j] == b[j]) {
                ++j;
            }
            if (j == min(a.size(), b.size())) {
                if (a.size() > b.size()) return "";
                continue;
            }
            if (after[a[j]].insert(b[j]).second) {
                ++indegree[b[j]];
            }
        }
        string order;
        for (auto [c, d] : indegree) {
            if (d == 0) {
                order += c;
            }
        }
        for (size_t i = 0; i < order.size(); ++i) {
            for (char next : after[order[i]]) {
                if (--indegree[next] == 0) {
                    order += next;
                }
            }
        }
        return order.size() == indegree.size() ? order : "";
    }
};
