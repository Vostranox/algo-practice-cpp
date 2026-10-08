#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Board = vector<vector<int>>;

static void run(const Board& board, int want) {
    Board arg = board;
    check(Solution().snakesAndLadders(arg), want, "board", board);
}

static vector<pair<int, int>> cells(int n) {
    vector<pair<int, int>> out(1);
    bool leftToRight = true;
    for (int r = n - 1; r >= 0; --r, leftToRight = !leftToRight) {
        for (int k = 0; k < n; ++k) {
            out.push_back({r, leftToRight ? k : n - 1 - k});
        }
    }
    return out;
}

static Board make(int n, const vector<pair<int, int>>& jumps) {
    Board b(n, vector<int>(n, -1));
    auto pos = cells(n);
    for (auto [from, to] : jumps) {
        b[pos[from].first][pos[from].second] = to;
    }
    return b;
}

static int fewest_moves(const Board& board) {
    int n = board.size(), last = n * n;
    auto pos = cells(n);
    vector<int> moves(last + 1, INT_MAX);
    moves[1] = 0;
    for (bool changed = true; changed;) {
        changed = false;
        for (int s = 1; s <= last; ++s) {
            if (moves[s] == INT_MAX) continue;
            for (int t = s + 1; t <= min(s + 6, last); ++t) {
                int to = board[pos[t].first][pos[t].second];
                if (to == -1) {
                    to = t;
                }
                if (moves[s] + 1 < moves[to]) {
                    moves[to] = moves[s] + 1, changed = true;
                }
            }
        }
    }
    return moves[last] == INT_MAX ? -1 : moves[last];
}

static Board random_board(Rng& rng, int n, double density) {
    vector<pair<int, int>> jumps;
    for (int s = 2; s < n * n; ++s) {
        if (rng.coin(density)) {
            int to = rng(1, n * n - 1);
            jumps.push_back({s, to >= s ? to + 1 : to});
        }
    }
    return make(n, jumps);
}

TEST(examples) {
    run({{-1, -1, -1, -1}, {-1, -1, -1, 2}, {-1, -1, -1, -1}, {-1, -1, 15, -1}}, 2);
    run({{-1, -1, -1, -1}, {16, -1, -1, -1}, {-1, -1, -1, -1}, {-1, 9, -1, -1}}, 2);
    run({{1, -1, -1}, {1, 1, 1}, {-1, 1, 1}}, -1);
}

TEST(edge_cases) {
    run(make(2, {}), 1);
    run(make(2, {{2, 1}, {3, 1}}), 1);
    run(make(3, {}), 2);
    run(make(5, {{2, 25}}), 1);
    run(make(3, {{7, 1}, {8, 1}}), 2);
    run(make(4, {{10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 1}, {15, 1}}), -1);
    run(make(4, {{2, 12}, {12, 1}}), 2);
    run(make(3, {{2, 8}, {8, 9}}), 2);
    run(make(4, {{2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 6}, {8, 1}, {9, 1}, {10, 1}, {11, 1}}), 3);
    run({{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, 16}, {-1, -1, -1, -1}}, 1);
    run({{-1, -1, -1, -1}, {-1, -1, -1, -1}, {16, -1, -1, -1}, {-1, -1, -1, -1}}, 2);
}

TEST(random) {
    Rng rng(198);
    for (int iter = 0; iter < 600; ++iter) {
        int n = rng(2, 6);
        Board b = random_board(rng, n, rng.pick(vector<double>{0.1, 0.3, 0.6}));
        run(b, fewest_moves(b));
    }
}

TEST(large) {
    run(make(20, {}), 67);
    vector<pair<int, int>> jumps;
    for (int s = 394; s < 400; ++s) {
        jumps.push_back({s, 1});
    }
    run(make(20, jumps), -1);
    jumps.clear();
    for (int s = 2; s < 400; ++s) {
        if (s % 5) {
            jumps.push_back({s, 1});
        }
    }
    run(make(20, jumps), 80);
    jumps.clear();
    for (int s = 2; s < 400; ++s) {
        jumps.push_back({s, 400});
    }
    run(make(20, jumps), 1);
    run(make(20, {{2, 399}, {399, 1}}), 2);
    Rng rng(1980);
    for (double density : {0.05, 0.1, 0.2, 0.35, 0.5}) {
        for (int k = 0; k < 4; ++k) {
            Board b = random_board(rng, 20, density);
            run(b, fewest_moves(b));
        }
    }
}

}
