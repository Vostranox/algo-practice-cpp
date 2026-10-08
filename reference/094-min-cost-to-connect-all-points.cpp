#include "prelude.hpp"

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size(), total = 0;
        vector<int> dist(n, INT_MAX);
        vector<bool> in_tree(n, false);
        dist[0] = 0;
        for (int step = 0; step < n; ++step) {
            int u = -1;
            for (int i = 0; i < n; ++i) {
                if (!in_tree[i] && (u < 0 || dist[i] < dist[u])) {
                    u = i;
                }
            }
            in_tree[u] = true;
            total += dist[u];
            for (int v = 0; v < n; ++v) {
                if (!in_tree[v]) {
                    dist[v] = min(dist[v], abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]));
                }
            }
        }
        return total;
    }
};
