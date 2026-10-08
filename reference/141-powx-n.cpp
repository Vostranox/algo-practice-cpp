#include "prelude.hpp"

class Solution {
public:
    double myPow(double x, int n) {
        int64_t e = n;
        if (e < 0) {
            x = 1 / x;
            e = -e;
        }
        double result = 1.0;
        for (; e; e >>= 1) {
            if (e & 1) {
                result *= x;
            }
            x *= x;
        }
        return result;
    }
};
