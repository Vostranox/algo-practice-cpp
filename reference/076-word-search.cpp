#include "prelude.hpp"

class Solution {
    int rows, cols;

    bool dfs(vector<vector<char>>& board, const string& word, int r, int c, int i) {
        if (i == static_cast<int>(word.size())) return true;
        if (r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] != word[i]) return false;
        board[r][c] = '#';
        bool found = dfs(board, word, r + 1, c, i + 1) || dfs(board, word, r - 1, c, i + 1) ||
                     dfs(board, word, r, c + 1, i + 1) || dfs(board, word, r, c - 1, i + 1);
        board[r][c] = word[i];
        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size(), cols = board[0].size();
        unordered_map<char, int> have;
        for (auto& row : board) {
            for (char ch : row) {
                ++have[ch];
            }
        }
        unordered_map<char, int> need;
        for (char ch : word) {
            if (++need[ch] > have[ch]) return false;
        }
        if (have[word.front()] > have[word.back()]) {
            reverse(word.begin(), word.end());
        }
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (dfs(board, word, r, c, 0)) return true;
            }
        }
        return false;
    }
};
