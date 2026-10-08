#include "prelude.hpp"

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> unlocks(numCourses);
        vector<int> missing(numCourses, 0);
        for (auto& p : prerequisites) {
            unlocks[p[1]].push_back(p[0]);
            ++missing[p[0]];
        }
        vector<int> ready;
        for (int c = 0; c < numCourses; ++c) {
            if (missing[c] == 0) {
                ready.push_back(c);
            }
        }
        int taken = 0;
        while (!ready.empty()) {
            int c = ready.back();
            ready.pop_back();
            ++taken;
            for (int next : unlocks[c]) {
                if (--missing[next] == 0) {
                    ready.push_back(next);
                }
            }
        }
        return taken == numCourses;
    }
};
