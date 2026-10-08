#include "prelude.hpp"

class Solution {
    struct TrieNode {
        TrieNode* child[26] = {};
        int children = 0;
        const string* word = nullptr;
    };

    vector<vector<char>>* board;
    vector<string> found;
    int R, C;

    void dfs(int r, int c, TrieNode* parent) {
        char ch = (*board)[r][c];
        TrieNode* node = parent->child[ch - 'a'];
        if (node->word) {
            found.push_back(*node->word);
            node->word = nullptr;
        }
        (*board)[r][c] = '#';
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        for (int d = 0; d < 4 && node->children; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nc >= 0 && nr < R && nc < C && (*board)[nr][nc] != '#' && node->child[(*board)[nr][nc] - 'a']) {
                dfs(nr, nc, node);
            }
        }
        (*board)[r][c] = ch;
        if (!node->children && !node->word) {
            parent->child[ch - 'a'] = nullptr;
            --parent->children;
            delete node;
        }
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode root;
        for (const string& w : words) {
            TrieNode* node = &root;
            for (char ch : w) {
                TrieNode*& next = node->child[ch - 'a'];
                if (!next) {
                    next = new TrieNode();
                    ++node->children;
                }
                node = next;
            }
            node->word = &w;
        }
        this->board = &board;
        R = board.size();
        C = board[0].size();
        found.clear();
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (root.child[board[r][c] - 'a']) {
                    dfs(r, c, &root);
                }
            }
        }
        return found;
    }
};
