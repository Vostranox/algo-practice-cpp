#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Rows = vector<string>;

static const Rows EXAMPLE = {
    "3...84.27", ".7265..1.", "..1..9.65",
    "..7.9...3", "..87.2.59", ".95.3.2..",
    ".2936.741", "7..92....", "....175..",
};

static const Rows SOLVED = {
    "356184927", "972653418", "481279365",
    "247596183", "138742659", "695831274",
    "529368741", "714925836", "863417592",
};

static Rows empty_rows() { return Rows(9, string(9, '.')); }

static Rows with_cells(const vector<tuple<int, int, char>>& cells) {
    Rows b = empty_rows();
    for (auto [r, c, d] : cells) {
        b[r][c] = d;
    }
    return b;
}

static void run(const Rows& rows, bool want) {
    vector<vector<char>> board;
    for (const string& row : rows) {
        board.emplace_back(row.begin(), row.end());
    }
    check(Solution().isValidSudoku(board), want, "board", rows);
}

static bool oracle(const Rows& b) {
    for (int p = 0; p < 81; ++p) {
        for (int q = p + 1; q < 81; ++q) {
            int r1 = p / 9, c1 = p % 9, r2 = q / 9, c2 = q % 9;
            if (b[r1][c1] == '.' || b[r1][c1] != b[r2][c2]) continue;
            if (r1 == r2 || c1 == c2 || (r1 / 3 == r2 / 3 && c1 / 3 == c2 / 3)) return false;
        }
    }
    return true;
}

TEST(examples) {
    run(EXAMPLE, true);
    Rows bad = EXAMPLE;
    bad[0][1] = '1';
    run(bad, false);
    run(empty_rows(), true);
}

TEST(single_rule_violations) {
    run(with_cells({{0, 0, '5'}, {0, 8, '5'}}), false);
    run(with_cells({{0, 4, '5'}, {8, 4, '5'}}), false);
    run(with_cells({{0, 0, '5'}, {1, 1, '5'}}), false);
    run(with_cells({{6, 6, '9'}, {8, 8, '9'}}), false);
    run(with_cells({{3, 5, '2'}, {5, 3, '2'}}), false);
    run(with_cells({{2, 2, '4'}, {3, 3, '4'}}), true);
    run(with_cells({{0, 2, '4'}, {1, 3, '4'}}), true);
    run(with_cells({{5, 0, '4'}, {6, 1, '4'}}), true);
    run(with_cells({{0, 0, '1'}, {0, 1, '2'}}), true);
}

TEST(edge_cases) {
    run(SOLVED, true);
    Rows full_bad = SOLVED;
    swap(full_bad[4][4], full_bad[4][5]);
    run(full_bad, false);
    Rows b = empty_rows();
    for (int c = 0; c < 8; ++c) {
        b[0][c] = char('1' + c);
    }
    b[1][8] = '9';
    run(b, true);
    run(with_cells({{4, 4, '7'}}), true);
}

TEST(random) {
    Rng rng(7);
    for (int it = 0; it < 300; ++it) {
        vector<int> perm(9), bands = {0, 1, 2}, stacks = {0, 1, 2};
        iota(perm.begin(), perm.end(), 0);
        rng.shuffle(perm);
        rng.shuffle(bands);
        rng.shuffle(stacks);
        vector<int> rows, cols;
        for (int band : bands) {
            vector<int> in = {0, 1, 2};
            rng.shuffle(in);
            for (int i : in) {
                rows.push_back(band * 3 + i);
            }
        }
        for (int st : stacks) {
            vector<int> in = {0, 1, 2};
            rng.shuffle(in);
            for (int i : in) {
                cols.push_back(st * 3 + i);
            }
        }
        double keep = rng.real();
        Rows b = empty_rows();
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (rng.coin(keep)) {
                    b[r][c] = char('1' + perm[SOLVED[rows[r]][cols[c]] - '1']);
                }
            }
        }
        if (rng.coin(0.7)) {
            b[rng(0, 8)][rng(0, 8)] = char('1' + rng(0, 8));
        }
        run(b, oracle(b));
    }
}

}
