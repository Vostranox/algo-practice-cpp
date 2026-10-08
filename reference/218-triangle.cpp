#include "prelude.hpp"

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> best = triangle.back();
        for (int i = static_cast<int>(triangle.size()) - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                best[j] = triangle[i][j] + min(best[j], best[j + 1]);
            }
        }
        return best[0];
    }
};
