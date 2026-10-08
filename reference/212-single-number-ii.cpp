#include "prelude.hpp"

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unsigned ones = 0, twos = 0;
        for (int x : nums) {
            unsigned u = x;
            ones = (ones ^ u) & ~twos;
            twos = (twos ^ u) & ~ones;
        }
        return static_cast<int>(ones);
    }
};
