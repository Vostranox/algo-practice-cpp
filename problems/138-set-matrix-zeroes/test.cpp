#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Matrix = vector<vector<int>>;

static Matrix zeroed(const Matrix& m) {
    int R = m.size(), C = m[0].size();
    vector<bool> row(R), col(C);
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (m[i][j] == 0) {
                row[i] = col[j] = true;
            }
        }
    }
    Matrix out = m;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (row[i] || col[j]) {
                out[i][j] = 0;
            }
        }
    }
    return out;
}

static void run(const Matrix& matrix, const Matrix& want) {
    Matrix m = matrix;
    Solution().setZeroes(m);
    ensure(!(m == matrix && want != matrix), "matrix is unchanged: setZeroes() must modify `matrix` in place",
           "matrix", matrix, "expected", want);
    check(m, want, "matrix", matrix);
}

static void run(const Matrix& matrix) { run(matrix, zeroed(matrix)); }

TEST(examples) {
    run({{3, 0, 5}, {2, 7, 1}, {4, 6, 8}}, {{0, 0, 0}, {2, 0, 1}, {4, 0, 8}});
    run({{1, 2, 3, 4}, {5, 0, 7, 8}, {9, 10, 11, 0}}, {{1, 0, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}});
    run({{0, 1, 2}, {3, 4, 5}}, {{0, 0, 0}, {0, 4, 5}});
}

TEST(zeros_in_first_row_or_column) {
    run({{1, 0, 3}, {4, 5, 6}, {7, 8, 9}}, {{0, 0, 0}, {4, 0, 6}, {7, 0, 9}});
    run({{1, 2, 3}, {0, 5, 6}, {7, 8, 9}}, {{0, 2, 3}, {0, 0, 0}, {0, 8, 9}});
    run({{1, 2, 0}, {4, 5, 6}}, {{0, 0, 0}, {4, 5, 0}});
    run({{1, 2}, {3, 4}, {0, 6}}, {{0, 2}, {0, 4}, {0, 0}});
    run({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}, {{0, 0, 0}, {0, 4, 5}, {0, 7, 8}});
    run({{1, 2, 3}, {4, 0, 6}, {7, 8, 9}}, {{1, 0, 3}, {0, 0, 0}, {7, 0, 9}});
    run({{5, 5, 5, 0}, {5, 5, 5, 5}, {0, 5, 5, 5}}, {{0, 0, 0, 0}, {0, 5, 5, 0}, {0, 0, 0, 0}});
}

TEST(edge_cases) {
    run({{0}}, {{0}});
    run({{1, 0, 2}}, {{0, 0, 0}});
    run({{1}, {0}, {2}}, {{0}, {0}, {0}});
    run({{0, 0}, {0, 0}}, {{0, 0}, {0, 0}});
    run({{0, 7}, {7, 0}}, {{0, 0}, {0, 0}});
    run({{-1, 2, -3}, {4, -5, 6}}, {{-1, 2, -3}, {4, -5, 6}});
    const int lo = INT_MIN, hi = INT_MAX;
    run({{lo, hi, 1}, {hi, 0, lo}, {1, lo, hi}}, {{lo, 0, 1}, {0, 0, 0}, {1, 0, hi}});
    run({{lo, 0}, {hi, lo}, {0, hi}}, {{0, 0}, {0, 0}, {0, 0}});
    run({{7}}, {{7}});
}

TEST(random) {
    Rng rng(73);
    const vector<int> common = {0, 1, 2, -1, INT_MAX, INT_MIN};
    for (int k = 0; k < 500; ++k) {
        int R = rng(1, 8), C = rng(1, 8);
        Matrix m(R, vector<int>(C));
        for (auto& row : m) {
            for (auto& v : row) {
                v = rng.coin(0.6) ? rng.pick(common) : rng(1, 9);
            }
        }
        run(m);
    }
    for (auto [R, C, zeros] : vector<tuple<int, int, int>>{{200, 200, 5}, {200, 1, 3}, {1, 200, 3}, {137, 200, 40}}) {
        Matrix m(R, vector<int>(C));
        for (auto& row : m) {
            for (auto& v : row) {
                v = static_cast<int>(rng.range(INT_MIN, INT_MAX)) | 1;
            }
        }
        for (int z = 0; z < zeros; ++z) {
            m[rng(0, R - 1)][rng(0, C - 1)] = 0;
        }
        run(m);
    }
}

}
