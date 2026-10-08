#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static int brute(int n) {
    vector<int> cols(n);
    iota(cols.begin(), cols.end(), 0);
    int count = 0;
    do {
        bool ok = true;
        for (int r1 = 0; r1 < n && ok; ++r1) {
            for (int r2 = r1 + 1; r2 < n && ok; ++r2) {
                ok = abs(cols[r1] - cols[r2]) != r2 - r1;
            }
        }
        count += ok;
    } while (next_permutation(cols.begin(), cols.end()));
    return count;
}

static const int COUNTS[10] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352};

TEST(examples) {
    check(Solution().totalNQueens(4), 2, "n", 4);
    check(Solution().totalNQueens(1), 1, "n", 1);
    check(Solution().totalNQueens(3), 0, "n", 3);
}

TEST(all_sizes) {
    for (int n = 1; n <= 9; ++n) {
        check(Solution().totalNQueens(n), COUNTS[n], "n", n);
    }
}

TEST(against_brute_force) {
    for (int n = 1; n <= 9; ++n) {
        check(Solution().totalNQueens(n), brute(n), "n", n);
    }
}

}
