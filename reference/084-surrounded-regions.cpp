#include "prelude.hpp"

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rows = board.size(), cols = board[0].size();
        vector<pair<int, int>> stack;
        for (int r = 0; r < rows; ++r) {
            stack.push_back({r, 0}), stack.push_back({r, cols - 1});
        }
        for (int c = 0; c < cols; ++c) {
            stack.push_back({0, c}), stack.push_back({rows - 1, c});
        }
        while (!stack.empty()) {
            auto [r, c] = stack.back();
            stack.pop_back();
            if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != 'O') continue;
            board[r][c] = 'T';
            stack.insert(stack.end(), {{r + 1, c}, {r - 1, c}, {r, c + 1}, {r, c - 1}});
        }
        for (auto& row : board) {
            for (char& ch : row) {
                ch = ch == 'T' ? 'O' : 'X';
            }
        }
    }
};
