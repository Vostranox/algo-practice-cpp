#include "prelude.hpp"

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        int other = 0;
        while (slow != other) {
            slow = nums[slow];
            other = nums[other];
        }
        return slow;
    }
};
