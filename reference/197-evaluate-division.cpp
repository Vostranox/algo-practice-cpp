#include "prelude.hpp"

class Solution {
    unordered_map<string, string> parent;
    unordered_map<string, double> ratio;

    string find(const string& x) {
        if (parent[x] == x) return x;
        string root = find(parent[x]);
        ratio[x] *= ratio[parent[x]];
        parent[x] = root;
        return root;
    }

    void add(const string& x) {
        if (!parent.count(x)) {
            parent[x] = x, ratio[x] = 1.0;
        }
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        for (size_t i = 0; i < equations.size(); ++i) {
            const string &a = equations[i][0], &b = equations[i][1];
            add(a), add(b);
            string ra = find(a), rb = find(b);
            if (ra == rb) continue;
            parent[ra] = rb;
            ratio[ra] = values[i] * ratio[b] / ratio[a];
        }
        vector<double> out;
        for (auto& q : queries) {
            const string &c = q[0], &d = q[1];
            if (!parent.count(c) || !parent.count(d) || find(c) != find(d)) {
                out.push_back(-1.0);
            } else {
                out.push_back(ratio[c] / ratio[d]);
            }
        }
        return out;
    }
};
