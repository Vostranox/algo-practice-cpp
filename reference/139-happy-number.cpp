#include "prelude.hpp"

class Solution {
    static int step(int k) {
        int total = 0;
        for (; k; k /= 10) {
            total += (k % 10) * (k % 10);
        }
        return total;
    }

public:
    bool isHappy(int n) {
        int slow = n, fast = step(n);
        while (fast != 1 && slow != fast) {
            slow = step(slow);
            fast = step(step(fast));
        }
        return fast == 1;
    }
};
