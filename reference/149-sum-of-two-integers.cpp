#include "prelude.hpp"

class Solution {
public:
    int getSum(int a, int b) {
        unsigned x = a, y = b;
        while (y) {
            unsigned carry = (x & y) << 1;
            x ^= y;
            y = carry;
        }
        return static_cast<int>(x);
    }
};
