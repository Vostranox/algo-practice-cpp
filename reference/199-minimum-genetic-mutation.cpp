#include "prelude.hpp"

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        unordered_set<string> unseen(bank.begin(), bank.end());
        unseen.erase(startGene);
        queue<string> q;
        q.push(startGene);
        for (int steps = 0; !q.empty(); ++steps) {
            for (int k = q.size(); k > 0; --k) {
                string g = q.front();
                q.pop();
                if (g == endGene) return steps;
                for (char& ch : g) {
                    char orig = ch;
                    for (char c : {'A', 'C', 'G', 'T'}) {
                        ch = c;
                        if (c != orig && unseen.erase(g)) {
                            q.push(g);
                        }
                    }
                    ch = orig;
                }
            }
        }
        return -1;
    }
};
