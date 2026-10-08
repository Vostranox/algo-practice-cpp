#include "prelude.hpp"

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int live = 0;
                for (int r = max(0, i - 1); r <= min(m - 1, i + 1); ++r) {
                    for (int c = max(0, j - 1); c <= min(n - 1, j + 1); ++c) {
                        if (r != i || c != j) {
                            live += board[r][c] & 1;
                        }
                    }
                }
                if (live == 3 || (live == 2 && (board[i][j] & 1))) {
                    board[i][j] |= 2;
                }
            }
        }
        for (auto& row : board) {
            for (int& cell : row) {
                cell >>= 1;
            }
        }
    }
};
