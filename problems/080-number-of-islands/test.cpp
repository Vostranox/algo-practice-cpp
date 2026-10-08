#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<char>>;

static Grid G(initializer_list<string> rows) {
    Grid g;
    for (const string& r : rows) {
        g.emplace_back(r.begin(), r.end());
    }
    return g;
}

static void run(const Grid& grid, int want) {
    Grid arg = grid;
    check(Solution().numIslands(arg), want, "grid", grid);
}

static int count_islands(const Grid& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> label(m, vector<int>(n, -1));
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (g[r][c] == '1') {
                label[r][c] = r * n + c;
            }
        }
    }
    for (bool changed = true; changed;) {
        changed = false;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (label[r][c] < 0) continue;
                int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int x = r + dr[d], y = c + dc[d];
                    if (x >= 0 && x < m && y >= 0 && y < n && label[x][y] >= 0 && label[x][y] < label[r][c]) {
                        label[r][c] = label[x][y];
                        changed = true;
                    }
                }
            }
        }
    }
    set<int> distinct;
    for (auto& row : label) {
        for (int v : row) {
            if (v >= 0) {
                distinct.insert(v);
            }
        }
    }
    return distinct.size();
}

TEST(examples) {
    run(G({"1100", "0101", "0001", "1011"}), 3);
    run(G({"101", "010", "101"}), 5);
    run(G({"00", "00"}), 0);
}

TEST(edge_cases) {
    run(G({"1"}), 1);
    run(G({"0"}), 0);
    run(G({"10101"}), 3);
    run(G({"1", "0", "1", "1"}), 2);
    run(G({"111", "101", "111"}), 1);
    run(G({"11111", "10001", "10101", "10001", "11111"}), 2);
    run(G({"0110", "1001", "0110"}), 4);
}

TEST(random) {
    Rng rng(80);
    for (int t = 0; t < 300; ++t) {
        int m = rng(1, 8), n = rng(1, 8);
        double p = rng.real();
        Grid grid(m, vector<char>(n));
        for (auto& row : grid) {
            for (char& ch : row) {
                ch = rng.coin(p) ? '1' : '0';
            }
        }
        run(grid, count_islands(grid));
    }
}

TEST(large) {
    Grid grid(300, vector<char>(300, '0'));
    for (int r = 0; r < 300; r += 2) {
        for (int c = 0; c < 300; c += 2) {
            grid[r][c] = '1';
        }
    }
    run(grid, 150 * 150);

    run(Grid(300, vector<char>(300, '1')), 1);

    grid.assign(300, vector<char>(300, '0'));
    for (int r = 0; r <= 30; ++r) {
        if (r % 2 == 0) {
            grid[r].assign(300, '1');
        } else {
            grid[r][(r / 2) % 2 == 0 ? 299 : 0] = '1';
        }
    }
    for (int r = 32; r < 300; ++r) {
        for (int c = 0; c < 300; ++c) {
            if ((r - 32) % 10 != 9 && c % 10 != 9) {
                grid[r][c] = '1';
            }
        }
    }
    run(grid, 1 + 27 * 30);
}

}
