#include "prelude.hpp"

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> out(n + 1);
        for (auto& t : times) {
            out[t[0]].push_back({t[1], t[2]});
        }
        vector<int> dist(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> heap;
        heap.push({0, k});
        dist[k] = 0;
        while (!heap.empty()) {
            auto [d, u] = heap.top();
            heap.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : out[u]) {
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    heap.push({dist[v], v});
                }
            }
        }
        int worst = *max_element(dist.begin() + 1, dist.end());
        return worst == INT_MAX ? -1 : worst;
    }
};
