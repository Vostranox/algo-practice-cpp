#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Board = vector<vector<char>>;

static Board B(initializer_list<string> rows) {
    Board b;
    for (const string& r : rows) {
        b.emplace_back(r.begin(), r.end());
    }
    return b;
}

static void run(const Board& board, const Board& want) {
    Board got = board;
    Solution().solve(got);
    if (board.size() * board[0].size() > 100 && got != want && got.size() == want.size()) {
        for (size_t r = 0; r < want.size(); ++r) {
            for (size_t c = 0; c < want[r].size() && c < got[r].size(); ++c) {
                if (got[r][c] != want[r][c]) {
                    fail("input:    <" + to_string(board.size()) + " x " + to_string(board[0].size()) +
                         " board built in the test>\nproblem:  cell (" + to_string(r) + ", " + to_string(c) +
                         ") should be " + repr(want[r][c]) + " but is " + repr(got[r][c]));
                }
            }
        }
    }
    check(got, want, "board", board);
}

static Board captured(const Board& b) {
    int m = b.size(), n = b[0].size();
    Board out = b;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (b[r][c] != 'O') continue;
            vector<vector<bool>> seen(m, vector<bool>(n));
            vector<pair<int, int>> stack{{r, c}};
            seen[r][c] = true;
            bool border = false;
            while (!stack.empty()) {
                auto [i, j] = stack.back();
                stack.pop_back();
                border |= i == 0 || i == m - 1 || j == 0 || j == n - 1;
                int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int x = i + dr[d], y = j + dc[d];
                    if (x >= 0 && x < m && y >= 0 && y < n && !seen[x][y] && b[x][y] == 'O') {
                        seen[x][y] = true;
                        stack.push_back({x, y});
                    }
                }
            }
            if (!border) {
                out[r][c] = 'X';
            }
        }
    }
    return out;
}

TEST(examples) {
    run(B({"OXXO", "XOOX", "XOXX", "OXOX"}), B({"OXXO", "XXXX", "XXXX", "OXOX"}));
    run(B({"XXXXX", "XOOOX", "XOXOX", "XOOOX", "XXXXX"}), B({"XXXXX", "XXXXX", "XXXXX", "XXXXX", "XXXXX"}));
    run(B({"XOX", "XOX", "XXX"}), B({"XOX", "XOX", "XXX"}));
}

TEST(edge_cases) {
    run(B({"XXX", "XOX", "XXX"}), B({"XXX", "XXX", "XXX"}));
    run(B({"O"}), B({"O"}));
    run(B({"X"}), B({"X"}));
    run(B({"OOO"}), B({"OOO"}));
    run(B({"O", "X", "O"}), B({"O", "X", "O"}));
    run(B({"OO", "OO"}), B({"OO", "OO"}));
    run(B({"XXXX", "XOXX", "XXOX", "XXXO"}), B({"XXXX", "XXXX", "XXXX", "XXXO"}));
    run(B({"XXXXX", "XOOOX", "XXXOX", "XXXOO"}), B({"XXXXX", "XOOOX", "XXXOX", "XXXOO"}));
    run(B({"XXXXXX", "XOOXOX", "XOXXOX", "XXXXOX", "XOOXXX", "XXXXXX"}),
        B({"XXXXXX", "XXXXXX", "XXXXXX", "XXXXXX", "XXXXXX", "XXXXXX"}));
}

TEST(random) {
    Rng rng(84);
    for (int t = 0; t < 300; ++t) {
        int m = rng(1, 8), n = rng(1, 8);
        double p = rng.real();
        Board b(m, vector<char>(n));
        for (auto& row : b) {
            for (char& ch : row) {
                ch = rng.coin(p) ? 'O' : 'X';
            }
        }
        run(b, captured(b));
    }
}

TEST(large) {
    const int n = 200;
    Board board(n, vector<char>(n, 'O')), want(n, vector<char>(n, 'X'));
    for (int i = 0; i < n; ++i) {
        board[1][i] = board[n - 2][i] = board[i][1] = board[i][n - 2] = 'X';
        want[0][i] = want[n - 1][i] = want[i][0] = want[i][n - 1] = 'O';
    }
    for (int i : {0, n - 1}) {
        board[i][1] = board[i][n - 2] = board[1][i] = board[n - 2][i] = 'O';
    }
    for (int i : {0, n - 1}) {
        want[i][1] = want[i][n - 2] = want[1][i] = want[n - 2][i] = 'O';
    }
    run(board, want);

    board.assign(n, vector<char>(n, 'X'));
    want.assign(n, vector<char>(n, 'X'));
    auto put = [&](int r, int c, bool survives) {
        board[r][c] = 'O';
        if (survives) {
            want[r][c] = 'O';
        }
    };
    for (int r = 0; r <= 30; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < n; ++c) {
                put(r, c, true);
            }
        } else {
            put(r, (r / 2) % 2 == 0 ? n - 1 : 0, true);
        }
    }
    for (int r = 32; r <= 60; ++r) {
        if (r % 2 == 0) {
            for (int c = 1; c < n - 1; ++c) {
                put(r, c, false);
            }
        } else {
            put(r, ((r - 32) / 2) % 2 == 0 ? n - 2 : 1, false);
        }
    }
    for (int r = 62; r < n - 1; r += 2) {
        for (int c = 0; c < n; c += 2) {
            put(r, c, c == 0);
        }
    }
    for (int c = 1; c < n; c += 2) {
        put(n - 1, c, true);
    }
    run(board, want);
}

}
