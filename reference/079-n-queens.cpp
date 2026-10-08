#include "prelude.hpp"

class Solution {
    int n;
    vector<vector<string>> res;
    vector<string> board;
    vector<bool> col, diag, anti;

    void dfs(int r) {
        if (r == n) {
            res.push_back(board);
            return;
        }
        for (int c = 0; c < n; ++c) {
            if (col[c] || diag[r - c + n - 1] || anti[r + c]) continue;
            col[c] = diag[r - c + n - 1] = anti[r + c] = true;
            board[r][c] = 'Q';
            dfs(r + 1);
            board[r][c] = '.';
            col[c] = diag[r - c + n - 1] = anti[r + c] = false;
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        board.assign(n, string(n, '.'));
        col.assign(n, false);
        diag.assign(2 * n - 1, false);
        anti.assign(2 * n - 1, false);
        dfs(0);
        return res;
    }
};
