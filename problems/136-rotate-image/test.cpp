#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Matrix = vector<vector<int>>;

static Matrix rotated(const Matrix& m) {
    int n = m.size();
    Matrix out(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out[j][n - 1 - i] = m[i][j];
        }
    }
    return out;
}

static void run(const Matrix& matrix, const Matrix& want) {
    Matrix m = matrix;
    Solution().rotate(m);
    ensure(!(m == matrix && want != matrix), "matrix is unchanged: rotate() must modify `matrix` in place",
           "matrix", matrix, "expected", want);
    check(m, want, "matrix", matrix);
}

static void run(const Matrix& matrix) { run(matrix, rotated(matrix)); }

TEST(examples) {
    run({{1, 2}, {3, 4}}, {{3, 1}, {4, 2}});
    run({{5, 1, 9}, {2, 4, 8}, {13, 3, 6}}, {{13, 2, 5}, {3, 4, 1}, {6, 8, 9}});
    run({{-7}}, {{-7}});
}

TEST(edge_cases) {
    run({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
        {{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}});
    run({{0, -1000}, {1000, 0}}, {{1000, 0}, {0, -1000}});
    run({{2, 2}, {2, 3}}, {{2, 2}, {3, 2}});
    run({{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}},
        {{21, 16, 11, 6, 1}, {22, 17, 12, 7, 2}, {23, 18, 13, 8, 3}, {24, 19, 14, 9, 4}, {25, 20, 15, 10, 5}});
    run({{1000}}, {{1000}});
}

TEST(four_rotations_restore) {
    Rng rng(136);
    for (int n : {2, 3, 6, 7, 20}) {
        Matrix original(n);
        for (auto& row : original) {
            row = rng.ints(n, -1000, 1000);
        }
        Matrix half = original;
        reverse(half.begin(), half.end());
        for (auto& row : half) {
            reverse(row.begin(), row.end());
        }
        Matrix m = original;
        Solution sol;
        sol.rotate(m);
        sol.rotate(m);
        check(m, half, "matrix", original, "rotations", 2);
        sol.rotate(m);
        sol.rotate(m);
        check(m, original, "matrix", original, "rotations", 4);
    }
}

TEST(random) {
    Rng rng(48);
    for (int k = 0; k < 500; ++k) {
        int n = rng(1, 20);
        Matrix m(n);
        for (auto& row : m) {
            row = rng.ints(n, -1000, 1000);
        }
        run(m);
    }
}

}
