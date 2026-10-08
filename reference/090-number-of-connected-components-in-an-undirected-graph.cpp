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
    int countComponents(int n, vector<vector<int>>& edges) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        int components = n;
        for (auto& e : edges) {
            int a = find(e[0]), b = find(e[1]);
            if (a != b) {
                parent[a] = b, --components;
            }
        }
        return components;
    }
};
