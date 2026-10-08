#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static const int COUNTS[10] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352};

static vector<vector<string>> solve(int n) {
    auto got = sorted(Solution().solveNQueens(n));
    for (auto& board : got) {
        bool shape = static_cast<int>(board.size()) == n;
        for (auto& row : board) {
            shape &= static_cast<int>(row.size()) == n && row.find_first_not_of("Q.") == string::npos;
        }
        ensure(shape, "each board must be " + to_string(n) + " strings of length " + to_string(n) +
                          " made of 'Q' and '.'", "n", n, "board", board);
        vector<int> cols;
        for (auto& row : board) {
            ensure(count(row.begin(), row.end(), 'Q') == 1, "every row needs exactly one queen", "n", n, "board", board);
            cols.push_back(row.find('Q'));
        }
        set<int> c, d, a;
        for (int r = 0; r < n; ++r) {
            c.insert(cols[r]), d.insert(r - cols[r]), a.insert(r + cols[r]);
        }
        ensure(static_cast<int>(c.size()) == n, "two queens share a column", "n", n, "board", board);
        ensure(static_cast<int>(d.size()) == n && static_cast<int>(a.size()) == n, "two queens share a diagonal", "n", n, "board", board);
    }
    if (auto d = adjacent_find(got.begin(), got.end()); d != got.end()) {
        ensure(false, "this board appears more than once: " + repr(*d), "n", n);
    }
    return got;
}

static vector<vector<string>> brute(int n) {
    vector<vector<string>> out;
    vector<int> cols(n);
    iota(cols.begin(), cols.end(), 0);
    do {
        bool ok = true;
        for (int r1 = 0; r1 < n; ++r1) {
            for (int r2 = r1 + 1; r2 < n; ++r2) {
                ok &= abs(cols[r1] - cols[r2]) != r2 - r1;
            }
        }
        if (!ok) continue;
        vector<string> board(n, string(n, '.'));
        for (int r = 0; r < n; ++r) {
            board[r][cols[r]] = 'Q';
        }
        out.push_back(board);
    } while (next_permutation(cols.begin(), cols.end()));
    return sorted(out);
}

TEST(examples) {
    check(solve(4), sorted(vector<vector<string>>{{".Q..", "...Q", "Q...", "..Q."}, {"..Q.", "Q...", "...Q", ".Q.."}}),
          "n", 4);
    check(solve(1), {{"Q"}}, "n", 1);
    check(solve(3), {}, "n", 3);
}

TEST(small_boards_exactly) {
    check(solve(2), {}, "n", 2);
    for (int n = 5; n <= 8; ++n) {
        check(solve(n), brute(n), "n", n);
    }
}

TEST(all_sizes) {
    for (int n = 1; n <= 9; ++n) {
        int got = solve(n).size();
        ensure(got == COUNTS[n], "there are " + to_string(COUNTS[n]) + " placements for this n, but " +
                                     to_string(got) + " were returned", "n", n);
    }
}

}
