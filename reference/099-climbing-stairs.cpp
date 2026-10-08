#include "prelude.hpp"

class Solution {
public:
    int climbStairs(int n) {
        int cur = 1, prev = 1;
        for (int i = 1; i < n; ++i) {
            int next = cur + prev;
            prev = cur;
            cur = next;
        }
        return cur;
    }
};
