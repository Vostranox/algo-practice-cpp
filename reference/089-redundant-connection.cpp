#include "prelude.hpp"

class Solution {
    vector<int> parent;

    int find(int x) {
        while (parent[x] != x) {
            x = parent[x] = parent[parent[x]];
        }
        return x;
    }

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        parent.resize(edges.size() + 1);
        iota(parent.begin(), parent.end(), 0);
        for (auto& e : edges) {
            int a = find(e[0]), b = find(e[1]);
            if (a == b) return e;
            parent[a] = b;
        }
        return {};
    }
};
