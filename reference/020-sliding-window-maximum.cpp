#include "prelude.hpp"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> q;
        vector<int> res;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            while (!q.empty() && nums[q.back()] <= nums[i]) {
                q.pop_back();
            }
            q.push_back(i);
            if (q.front() <= i - k) {
                q.pop_front();
            }
            if (i >= k - 1) {
                res.push_back(nums[q.front()]);
            }
        }
        return res;
    }
};
