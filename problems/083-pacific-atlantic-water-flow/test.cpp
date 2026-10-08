#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;

static void run(const Grid& heights, const Grid& want) {
    Grid arg = heights;
    Grid got = Solution().pacificAtlantic(arg);
    for (auto& cell : got) {
        ensure(cell.size() == 2, "every cell should be a {row, col} pair", "got", got, "heights", heights);
    }
    check(sorted(got), sorted(want), "heights", heights);
}

static Grid both_oceans(const Grid& h) {
    int m = h.size(), n = h[0].size();
    Grid out;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            vector<vector<bool>> seen(m, vector<bool>(n));
            vector<pair<int, int>> stack{{r, c}};
            seen[r][c] = true;
            bool pacific = false, atlantic = false;
            while (!stack.empty()) {
                auto [i, j] = stack.back();
                stack.pop_back();
                pacific |= i == 0 || j == 0;
                atlantic |= i == m - 1 || j == n - 1;
                int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int x = i + dr[d], y = j + dc[d];
                    if (x >= 0 && x < m && y >= 0 && y < n && !seen[x][y] && h[x][y] <= h[i][j]) {
                        seen[x][y] = true;
                        stack.push_back({x, y});
                    }
                }
            }
            if (pacific && atlantic) {
                out.push_back({r, c});
            }
        }
    }
    return out;
}

static Grid all_cells(int m, int n) {
    Grid out;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            out.push_back({r, c});
        }
    }
    return out;
}

TEST(examples) {
    run({{1, 2, 3}, {8, 9, 4}, {7, 6, 5}}, {{0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}});
    run({{1, 2}, {4, 3}}, {{0, 1}, {1, 0}, {1, 1}});
    run({{5}}, {{0, 0}});
}

TEST(edge_cases) {
    run({{3, 1, 4, 1, 5}}, all_cells(1, 5));
    run({{2}, {7}, {1}}, all_cells(3, 1));
    run({{4, 4, 4}, {4, 4, 4}}, all_cells(2, 3));
    run({{0, 0, 0}, {0, 9, 0}, {0, 0, 0}}, all_cells(3, 3));
    run({{5, 1, 5}, {1, 0, 1}, {5, 1, 5}}, {{0, 2}, {2, 0}});
    run({{1, 1, 3}, {1, 5, 2}, {3, 2, 2}}, {{0, 2}, {1, 1}, {2, 0}});
}

TEST(random) {
    Rng rng(83);
    for (int t = 0; t < 300; ++t) {
        int m = rng(1, 8), n = rng(1, 8), top = rng.pick(vector<int>{2, 5, 100000});
        Grid h(m, vector<int>(n));
        for (auto& row : h) {
            for (int& x : row) {
                x = rng(0, top);
            }
        }
        run(h, both_oceans(h));
    }
}

TEST(large) {
    const int m = 200, n = 200;
    Grid h(m, vector<int>(n)), want;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            h[r][c] = r + c;
        }
    }
    for (int c = 0; c < n; ++c) {
        want.push_back({m - 1, c});
    }
    for (int r = 0; r < m - 1; ++r) {
        want.push_back({r, n - 1});
    }
    run(h, want);
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            h[r][c] = (m - 1 - r) + (n - 1 - c);
        }
    }
    want.clear();
    for (int c = 0; c < n; ++c) {
        want.push_back({0, c});
    }
    for (int r = 1; r < m; ++r) {
        want.push_back({r, 0});
    }
    run(h, want);
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            h[r][c] = abs(r - c);
        }
    }
    run(h, {{0, n - 1}, {m - 1, 0}});
    run(Grid(m, vector<int>(n, 100000)), all_cells(m, n));
}

}
