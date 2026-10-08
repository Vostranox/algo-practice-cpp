#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static string bitset_sum(const string& a, const string& b) {
    bitset<10002> x(a), c(b);
    while (c.any()) {
        bitset<10002> carry = (x & c) << 1;
        x ^= c;
        c = carry;
    }
    string s = x.to_string();
    size_t nz = s.find('1');
    return nz == string::npos ? "0" : s.substr(nz);
}

static string small_sum(const string& a, const string& b) {
    uint64_t v = stoull(a, nullptr, 2) + stoull(b, nullptr, 2);
    string s;
    for (; v; v >>= 1) {
        s += char('0' + (v & 1));
    }
    reverse(s.begin(), s.end());
    return s.empty() ? "0" : s;
}

static void run(const string& a, const string& b, const string& want) {
    string got = Solution().addBinary(a, b);
    if (got != want && got.size() == want.size() && want.size() > 40) {
        size_t i = 0;
        while (got[i] == want[i]) {
            ++i;
        }
        ensure(false, "right length, but the bits first differ at index " + to_string(i), "a", a, "b", b,
               "expected", want, "got", got);
    }
    check(got, want, "a", a, "b", b);
}

static void run(const string& a, const string& b) {
    run(a, b, max(a.size(), b.size()) <= 62 ? small_sum(a, b) : bitset_sum(a, b));
}

static string number(Rng& rng, int len) {
    return len == 1 && rng.coin(0.3) ? "0" : "1" + rng.str(len - 1, "01");
}

TEST(examples) {
    run("101", "11", "1000");
    run("1101", "1011", "11000");
    run("0", "110", "110");
}

TEST(edge_cases) {
    run("0", "0", "0");
    run("0", "1", "1");
    run("1", "0", "1");
    run("1", "1", "10");
    run("1011", "0", "1011");
    run("111", "1", "1000");
    run("1", "111", "1000");
    run("1111", "1111", "11110");
    run("100", "110010", "110110");
    run("1010", "101", "1111");
    run("10", "10", "100");
    run("11", "11", "110");
    run("1000000", "1", "1000001");
}

TEST(long_numbers) {
    const string ones(10000, '1');
    run(ones, "1", "1" + string(10000, '0'));
    run("1", ones, "1" + string(10000, '0'));
    run(ones, ones, ones + "0");
    run("1" + string(9999, '0'), "1" + string(9999, '0'), "1" + string(10000, '0'));
    run("1" + string(9999, '0'), "0", "1" + string(9999, '0'));
    run(string(5000, '1') + string(5000, '0'), string(5000, '1'), string(10000, '1'));
    Rng rng(67);
    for (int k = 0; k < 10; ++k) {
        string a = number(rng, 10000), b = number(rng, rng(1, 10000));
        run(a, b);
        run(b, a);
    }
}

TEST(random) {
    Rng rng(6767);
    for (int k = 0; k < 5000; ++k) {
        run(number(rng, rng(1, 62)), number(rng, rng(1, 62)));
    }
    for (int k = 0; k < 200; ++k) {
        run(number(rng, rng(60, 300)), number(rng, rng(1, 300)));
    }
}

}
