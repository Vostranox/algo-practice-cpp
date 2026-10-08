#include "prelude.hpp"

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize) return false;
        map<int64_t, int> count;
        for (int x : hand) {
            ++count[x];
        }
        for (auto& [x, k] : count) {
            if (k == 0) continue;
            int need = k;
            for (int64_t v = x; v < x + groupSize; ++v) {
                auto it = count.find(v);
                if (it == count.end() || it->second < need) return false;
                it->second -= need;
            }
        }
        return true;
    }
};
