#include "prelude.hpp"

class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;
        for (; n; n &= n - 1) {
            ++count;
        }
        return count;
    }
};
