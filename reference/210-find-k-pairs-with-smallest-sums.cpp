#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        using Item = tuple<int64_t, int, int>;
        priority_queue<Item, vector<Item>, greater<Item>> heap;
        for (int i = 0; i < static_cast<int>(nums1.size()) && i < k; ++i) {
            heap.emplace(static_cast<int64_t>(nums1[i]) + nums2[0], i, 0);
        }
        vector<vector<int>> res;
        while (static_cast<int>(res.size()) < k && !heap.empty()) {
            auto [sum, i, j] = heap.top();
            heap.pop();
            res.push_back({nums1[i], nums2[j]});
            if (j + 1 < static_cast<int>(nums2.size())) {
                heap.emplace(static_cast<int64_t>(nums1[i]) + nums2[j + 1], i, j + 1);
            }
        }
        return res;
    }
};
