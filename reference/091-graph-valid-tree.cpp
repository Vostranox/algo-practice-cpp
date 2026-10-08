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
    bool validTree(int n, vector<vector<int>>& edges) {
        if (static_cast<int>(edges.size()) != n - 1) return false;
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        for (auto& e : edges) {
            int a = find(e[0]), b = find(e[1]);
            if (a == b) return false;
            parent[a] = b;
        }
        return true;
    }
};
