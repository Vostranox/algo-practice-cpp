#include "prelude.hpp"

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size(), last = n * n;
        auto jump = [&](int s) {
            int r = (s - 1) / n, c = (s - 1) % n;
            if (r % 2) {
                c = n - 1 - c;
            }
            int to = board[n - 1 - r][c];
            return to == -1 ? s : to;
        };
        vector<int> moves(last + 1, -1);
        moves[1] = 0;
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int s = q.front();
            q.pop();
            if (s == last) return moves[s];
            for (int t = s + 1; t <= min(s + 6, last); ++t) {
                int to = jump(t);
                if (moves[to] == -1) {
                    moves[to] = moves[s] + 1;
                    q.push(to);
                }
            }
        }
        return -1;
    }
};
