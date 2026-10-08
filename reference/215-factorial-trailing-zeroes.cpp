#include "prelude.hpp"

class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0;
        for (; n; n /= 5) {
            count += n / 5;
        }
        return count;
    }
};
