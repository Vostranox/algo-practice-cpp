#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static uint32_t reversed32(uint32_t n) {
    string s = bitset<32>(n).to_string();
    reverse(s.begin(), s.end());
    return static_cast<uint32_t>(bitset<32>(s).to_ulong());
}

static void run(uint32_t n, uint32_t want) {
    check(Solution().reverseBits(n), want, "n", n, "bits", bitset<32>(n).to_string());
}
static void run(uint32_t n) { run(n, reversed32(n)); }

TEST(examples) {
    run(1u, 2147483648u);
    run(6u, 1610612736u);
    run(4294967293u, 3221225471u);
}

TEST(edge_cases) {
    run(0u, 0u);
    run(0xFFFFFFFFu, 0xFFFFFFFFu);
    run(0x80000000u, 1u);
    run(0x0000FFFFu, 0xFFFF0000u);
    run(0xFFFF0000u, 0x0000FFFFu);
    run(0x80000001u, 0x80000001u);
    run(0x0000000Fu, 0xF0000000u);
    run(0x12345678u, 0x1E6A2C48u);
    run(2u, 1u << 30);
    run(0x7FFFFFFFu, 0xFFFFFFFEu);
}

TEST(random) {
    Rng rng(190);
    for (int k = 0; k < 20000; ++k) {
        run(static_cast<uint32_t>(rng.range(0, 0xFFFFFFFFLL)));
    }
    for (int k = 0; k < 32; ++k) {
        run(1u << k, 1u << (31 - k));
    }
}

}
