#include "prelude.hpp"

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int x : nums) {
            ++count[x];
        }
        vector<vector<int>> buckets(nums.size() + 1);
        for (auto [x, c] : count) {
            buckets[c].push_back(x);
        }
        vector<int> res;
        for (int c = static_cast<int>(nums.size()); c > 0 && static_cast<int>(res.size()) < k; --c) {
            for (int x : buckets[c]) {
                res.push_back(x);
                if (static_cast<int>(res.size()) == k) break;
            }
        }
        return res;
    }
};
