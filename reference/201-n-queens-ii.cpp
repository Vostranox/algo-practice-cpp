#include "prelude.hpp"

class Solution {
    int n;

    int count(int row, unsigned cols, unsigned diag, unsigned anti) {
        if (row == n) return 1;
        int total = 0;
        for (int c = 0; c < n; ++c) {
            unsigned cb = 1u << c, db = 1u << (row - c + n - 1), ab = 1u << (row + c);
            if ((cols & cb) || (diag & db) || (anti & ab)) continue;
            total += count(row + 1, cols | cb, diag | db, anti | ab);
        }
        return total;
    }

public:
    int totalNQueens(int n) {
        this->n = n;
        return count(0, 0, 0, 0);
    }
};
