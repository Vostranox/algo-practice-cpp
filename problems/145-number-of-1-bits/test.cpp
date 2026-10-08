#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static string binary(int n) {
    string s = bitset<32>(n).to_string();
    return s.substr(min(s.find('1'), s.size() - 1));
}

static void run(int n, int want) { check(Solution().hammingWeight(n), want, "n", n, "binary", binary(n)); }
static void run(int n) { run(n, static_cast<int>(bitset<32>(n).count())); }

TEST(examples) {
    run(13, 3);
    run(64, 1);
    run(2147483645, 30);
}

TEST(edge_cases) {
    run(1, 1);
    run(2, 1);
    run(3, 2);
    run(INT_MAX, 31);
    run(1 << 30, 1);
    run(INT_MAX - 1, 30);
    run(0x55555555, 16);
    run(0x2AAAAAAA, 15);
    run(0x40000001, 2);
}

TEST(random) {
    Rng rng(191);
    for (int k = 0; k < 20000; ++k) {
        run(rng(1, INT_MAX));
    }
    for (int k = 0; k < 31; ++k) {
        run(1 << k, 1);
        run(static_cast<int>((int64_t{1} << (k + 1)) - 1), k + 1);
    }
}

}
