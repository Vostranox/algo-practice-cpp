#include "prelude.hpp"

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> unlocks(numCourses);
        vector<int> missing(numCourses, 0), order;
        for (auto& p : prerequisites) {
            unlocks[p[1]].push_back(p[0]);
            ++missing[p[0]];
        }
        for (int c = 0; c < numCourses; ++c) {
            if (missing[c] == 0) {
                order.push_back(c);
            }
        }
        for (size_t i = 0; i < order.size(); ++i) {
            for (int next : unlocks[order[i]]) {
                if (--missing[next] == 0) {
                    order.push_back(next);
                }
            }
        }
        if (static_cast<int>(order.size()) < numCourses) return {};
        return order;
    }
};
