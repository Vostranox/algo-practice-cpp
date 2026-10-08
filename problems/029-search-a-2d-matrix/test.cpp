#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Matrix = vector<vector<int>>;

static void run(const Matrix& matrix, int target, bool want) {
    Matrix arg = matrix;
    check(Solution().searchMatrix(arg, target), want, "matrix", matrix, "target", target);
}

static bool oracle(const Matrix& matrix, int target) {
    for (auto& row : matrix) {
        for (int x : row) {
            if (x == target) return true;
        }
    }
    return false;
}

static Matrix make_matrix(Rng& rng, int m, int n, int lo, int hi, double dup_chance = 0) {
    vector<int> all(hi - lo + 1);
    iota(all.begin(), all.end(), lo);
    rng.shuffle(all);
    all.resize(m * n);
    all = sorted(all);
    Matrix rows(m);
    for (int r = 0; r < m; ++r) {
        rows[r].assign(all.begin() + r * n, all.begin() + (r + 1) * n);
        for (int c = 1; c < n; ++c) {
            if (rng.coin(dup_chance)) {
                rows[r][c] = rows[r][c - 1];
            }
        }
    }
    return rows;
}

static const Matrix EXAMPLE = {{1, 4, 6, 9}, {12, 13, 20, 25}, {31, 40, 41, 50}};

TEST(examples) {
    run(EXAMPLE, 20, true);
    run(EXAMPLE, 10, false);
    run({{-5}}, -5, true);
}

TEST(edge_cases) {
    run({{-5}}, -6, false);
    run({{-5}}, -4, false);
    for (int target : {1, 9, 12, 25, 31, 50}) {
        run(EXAMPLE, target, true);
    }
    for (int target : {0, 11, 26, 30, 51, 10000, -10000}) {
        run(EXAMPLE, target, false);
    }
    run({{1, 3, 5, 7, 9}}, 7, true);
    run({{1, 3, 5, 7, 9}}, 8, false);
    run({{2}, {4}, {6}, {8}}, 6, true);
    run({{2}, {4}, {6}, {8}}, 5, false);
    run({{3, 3, 3}, {4, 4, 4}}, 4, true);
    run({{3, 3, 3}, {5, 5, 5}}, 4, false);
    run({{-10000, 0}, {1, 10000}}, 10000, true);
}

TEST(every_cell) {
    Rng rng(29);
    for (int m = 1; m <= 7; ++m) {
        for (int n = 1; n <= 7; ++n) {
            Matrix matrix = make_matrix(rng, m, n, -80, 80, 0.3);
            for (int target = matrix[0][0] - 2; target <= matrix.back().back() + 2; ++target) {
                run(matrix, target, oracle(matrix, target));
            }
        }
    }
    for (auto [m, n] : {pair{100, 100}, pair{100, 1}, pair{1, 100}, pair{37, 100}, pair{100, 61}}) {
        Matrix matrix = make_matrix(rng, m, n, -10000, 10000, 0.1), arg = matrix;
        vector<bool> present(20001, false);
        for (auto& row : matrix) {
            for (int x : row) {
                present[x + 10000] = true;
            }
        }
        for (int target = -10000; target <= 10000; ++target) {
            check(Solution().searchMatrix(arg, target), static_cast<bool>(present[target + 10000]),
                  "matrix", matrix, "target", target);
        }
        ensure(arg == matrix, "searchMatrix() must not modify the matrix");
    }
}

TEST(many_searches) {
    Matrix matrix(100, vector<int>(100));
    for (int r = 0; r < 100; ++r) {
        for (int c = 0; c < 100; ++c) {
            matrix[r][c] = 2 * (100 * r + c) - 9999;
        }
    }
    Matrix arg = matrix;
    Rng rng(74);
    for (int q = 0; q < 1000000; ++q) {
        int target = rng(-10000, 10000);
        bool want = target >= -9999 && target <= 9999 && (target + 9999) % 2 == 0;
        bool got = Solution().searchMatrix(arg, target);
        if (got != want) {
            check(got, want, "matrix", matrix, "target", target);
        }
        if (arg.size() != 100) {
            fail("searchMatrix() must not modify the matrix");
        }
    }
    ensure(arg == matrix, "searchMatrix() must not modify the matrix");
}

}
