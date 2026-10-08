#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Board = vector<vector<int>>;

static Board next_gen(const Board& b) {
    int R = b.size(), C = b[0].size();
    Board pad(R + 2, vector<int>(C + 2, 0));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            pad[i + 1][j + 1] = b[i][j];
        }
    }
    Board out(R, vector<int>(C));
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            int live = -pad[i][j];
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    live += pad[i + di][j + dj];
                }
            }
            out[i - 1][j - 1] = live == 3 || (live == 2 && pad[i][j] == 1);
        }
    }
    return out;
}

static void run(const Board& board, const Board& want) {
    Board b = board;
    Solution().gameOfLife(b);
    ensure(!(b == board && want != board), "board is unchanged: gameOfLife() must update `board` in place",
           "board", board, "expected", want);
    check(b, want, "board", board);
}

static void run(const Board& board) { run(board, next_gen(board)); }

static Board random_board(Rng& rng, int R, int C, double alive) {
    Board b(R, vector<int>(C));
    for (auto& row : b) {
        for (auto& v : row) {
            v = rng.coin(alive);
        }
    }
    return b;
}

TEST(examples) {
    run({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}}, {{0, 0, 0}, {1, 1, 1}, {0, 0, 0}});
    run({{1, 0, 0, 1}, {0, 1, 1, 0}, {1, 0, 0, 0}}, {{0, 1, 1, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}});
    run({{1, 1}, {1, 1}}, {{1, 1}, {1, 1}});
}

TEST(edge_cases) {
    run({{1}}, {{0}});
    run({{0}}, {{0}});
    run({{1, 1}}, {{0, 0}});
    run({{1, 1, 1}}, {{0, 1, 0}});
    run({{1}, {1}, {1}, {1}}, {{0}, {1}, {1}, {0}});
    run({{1, 1}, {1, 0}}, {{1, 1}, {1, 1}});
    run({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}});
    run({{1, 0, 1}, {0, 0, 0}, {1, 0, 1}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    run({{0, 1, 0}, {1, 0, 1}, {0, 1, 0}}, {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});
    run({{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}});
    run({{0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}});
    run({{0, 1, 0}, {1, 0, 1}, {1, 0, 0}}, {{0, 1, 0}, {1, 0, 0}, {0, 1, 0}});
}

TEST(patterns) {
    Solution sol;
    auto steps = [&](Board b, int k) {
        for (int s = 0; s < k; ++s) {
            Board before = b, want = next_gen(b);
            sol.gameOfLife(b);
            check(b, want, "board", before, "step", s + 1);
        }
        return b;
    };
    Board toad = {{0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0},
                  {0, 0, 1, 1, 1, 0},
                  {0, 1, 1, 1, 0, 0},
                  {0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0}};
    check(steps(toad, 2), toad, "board", toad, "steps", 2);
    Board beacon = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 1}};
    check(steps(beacon, 1), {{1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 1}}, "board", beacon, "steps", 1);
    check(steps(beacon, 2), beacon, "board", beacon, "steps", 2);
    Board beehive = {{0, 1, 1, 0}, {1, 0, 0, 1}, {0, 1, 1, 0}};
    check(steps(beehive, 1), beehive, "board", beehive, "steps", 1);
    Board glider(25, vector<int>(25, 0)), moved = glider;
    for (auto [r, c] : vector<pair<int, int>>{{0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}}) {
        glider[r][c] = 1;
        moved[r + 5][c + 5] = 1;
    }
    check(steps(glider, 20), moved, "board", glider, "steps", 20);
    Board block(25, vector<int>(25, 0));
    for (int r : {23, 24}) {
        for (int c : {23, 24}) {
            block[r][c] = 1;
        }
    }
    check(steps(glider, 92), block, "board", glider, "steps", 92);
}

TEST(random) {
    Rng rng(289);
    for (int k = 0; k < 1500; ++k) {
        int R = rng(1, 8), C = rng(1, 8);
        run(random_board(rng, R, C, rng.pick(vector<double>{0.2, 0.4, 0.5, 0.7})));
    }
    for (int k = 0; k < 100; ++k) {
        run(random_board(rng, rng(20, 25), rng(20, 25), 0.35));
    }
    for (int k = 0; k < 20; ++k) {
        run(random_board(rng, 25, 25, 1.0 - 0.05 * k));
    }
}

}
