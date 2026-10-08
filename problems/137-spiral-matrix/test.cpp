#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Matrix = vector<vector<int>>;

static vector<int> spiral(const Matrix& m) {
    int R = m.size(), C = m[0].size();
    vector<vector<bool>> seen(R, vector<bool>(C));
    const int dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};
    vector<int> out;
    for (int r = 0, c = 0, d = 0, k = 0; k < R * C; ++k) {
        out.push_back(m[r][c]);
        seen[r][c] = true;
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C || seen[nr][nc]) {
            d = (d + 1) % 4;
            nr = r + dr[d], nc = c + dc[d];
        }
        r = nr, c = nc;
    }
    return out;
}

static void run(const Matrix& matrix, const vector<int>& want) {
    Matrix arg = matrix;
    check(Solution().spiralOrder(arg), want, "matrix", matrix);
}

static void run(const Matrix& matrix) { run(matrix, spiral(matrix)); }

TEST(examples) {
    run({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}}, {2, 4, 6, 12, 18, 16, 14, 8, 10});
    run({{1, 2, 3, 4}, {10, 11, 12, 5}, {9, 8, 7, 6}}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    run({{7}, {8}, {9}}, {7, 8, 9});
}

TEST(thin_shapes) {
    run({{5}}, {5});
    run({{1, 2, 3, 4, 5}}, {1, 2, 3, 4, 5});
    run({{1}, {2}, {3}, {4}}, {1, 2, 3, 4});
    run({{1, 2}}, {1, 2});
    run({{1}, {2}}, {1, 2});
    run({{1, 2}, {3, 4}}, {1, 2, 4, 3});
    run({{1, 2, 3}, {4, 5, 6}}, {1, 2, 3, 6, 5, 4});
    run({{1, 2}, {3, 4}, {5, 6}}, {1, 2, 4, 6, 5, 3});
    run({vector<int>(10, -100)}, vector<int>(10, -100));
    run(Matrix(10, vector<int>{100}), vector<int>(10, 100));
}

TEST(inner_row_or_column_left_over) {
    run({{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}},
        {1, 2, 3, 4, 5, 10, 15, 14, 13, 12, 11, 6, 7, 8, 9});
    run({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}, {1, 2, 3, 6, 9, 12, 11, 10, 7, 4, 5, 8});
    run({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}, {17, 18, 19, 20}},
        {1, 2, 3, 4, 8, 12, 16, 20, 19, 18, 17, 13, 9, 5, 6, 7, 11, 15, 14, 10});
    run({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
        {1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10});
    run({{0, -1, -2, -3, -4}, {-5, -6, -7, -8, -9}, {1, 2, 3, 4, 5}},
        {0, -1, -2, -3, -4, -9, 5, 4, 3, 2, 1, -5, -6, -7, -8});
}

TEST(random) {
    Rng rng(54);
    for (int m = 1; m <= 10; ++m) {
        for (int n = 1; n <= 10; ++n) {
            for (int k = 0; k < 3; ++k) {
                Matrix a(m);
                for (auto& row : a) {
                    row = rng.ints(n, -100, 100);
                }
                run(a);
            }
            Matrix distinct(m, vector<int>(n));
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    distinct[i][j] = i * n + j;
                }
            }
            run(distinct);
        }
    }
}

}
