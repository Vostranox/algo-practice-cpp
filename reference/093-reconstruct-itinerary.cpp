#include "prelude.hpp"

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, vector<string>> out;
        for (auto& t : tickets) {
            out[t[0]].push_back(t[1]);
        }
        for (auto& [from, to] : out) {
            sort(to.rbegin(), to.rend());
        }
        vector<string> route, stack{"JFK"};
        while (!stack.empty()) {
            vector<string>& next = out[stack.back()];
            if (next.empty()) {
                route.push_back(stack.back());
                stack.pop_back();
            } else {
                string to = next.back();
                next.pop_back();
                stack.push_back(to);
            }
        }
        reverse(route.begin(), route.end());
        return route;
    }
};
