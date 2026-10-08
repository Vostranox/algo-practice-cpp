#include "prelude.hpp"

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> count(n + 1, 0);
        for (int c : citations) {
            ++count[min(c, n)];
        }
        for (int h = n, atLeast = 0; h > 0; --h) {
            atLeast += count[h];
            if (atLeast >= h) return h;
        }
        return 0;
    }
};
