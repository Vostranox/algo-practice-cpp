#include "prelude.hpp"

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix[0].size(), best = 0;
        vector<int> side(n + 1, 0);
        for (auto& row : matrix) {
            int diag = 0;
            for (int c = 1; c <= n; ++c) {
                int above = side[c];
                side[c] = row[c - 1] == '1' ? 1 + min({above, side[c - 1], diag}) : 0;
                diag = above;
                best = max(best, side[c]);
            }
        }
        return best * best;
    }
};
