#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static string add(const string& a, const string& b) {
    string out;
    int carry = 0;
    for (int i = a.size() - 1, j = b.size() - 1; i >= 0 || j >= 0 || carry; --i, --j) {
        int s = carry + (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j] - '0' : 0);
        out.push_back(char('0' + s % 10));
        carry = s / 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

static string times_digit(const string& a, int d) {
    string out = "0";
    for (int k = 0; k < d; ++k) {
        out = add(out, a);
    }
    return out;
}

static string product(const string& a, const string& b) {
    string res = "0";
    for (char c : b) {
        res = add(res + "0", times_digit(a, c - '0'));
    }
    size_t nz = res.find_first_not_of('0');
    return nz == string::npos ? "0" : res.substr(nz);
}

static void run(const string& num1, const string& num2, const string& want) {
    string got = Solution().multiply(num1, num2);
    if (got != want && got.size() == want.size() && want.size() > 40) {
        size_t i = 0;
        while (got[i] == want[i]) {
            ++i;
        }
        ensure(false, "right length, but the digits first differ at index " + to_string(i),
               "num1", num1, "num2", num2, "expected", want, "got", got);
    }
    check(got, want, "num1", num1, "num2", num2);
}

static void run(const string& num1, const string& num2) { run(num1, num2, product(num1, num2)); }

static string number(Rng& rng, int len) {
    return rng.str(1, "123456789") + rng.str(len - 1, "0123456789");
}

TEST(examples) {
    run("12", "12", "144");
    run("123", "45", "5535");
    run("0", "987", "0");
}

TEST(edge_cases) {
    run("0", "0", "0");
    run("1", "1", "1");
    run("9", "9", "81");
    run("2", "3", "6");
    run("987654321", "0", "0");
    run("0", string(200, '5'), "0");
    run("1", "100200300", "100200300");
    run("100200300", "1", "100200300");
    run("10", "10", "100");
    run("100", "1000", "100000");
    run("999", "999", "998001");
    run("99999", "99999", "9999800001");
    run(string(200, '1'), "0", "0");
}

TEST(long_numbers) {
    run(string(200, '9'), string(200, '9'), string(199, '9') + "8" + string(199, '0') + "1");
    run("1" + string(199, '0'), "1" + string(199, '0'), "1" + string(398, '0'));
    run(string(200, '5'), "2", "1" + string(199, '1') + "0");
    Rng rng(43);
    for (int k = 0; k < 20; ++k) {
        string a = number(rng, 200), b = number(rng, rng(1, 200));
        run(a, b);
        run(b, a);
    }
}

TEST(random) {
    Rng rng(4343);
    for (int k = 0; k < 2000; ++k) {
        string a = rng.coin(0.05) ? "0" : number(rng, rng(1, 25));
        string b = rng.coin(0.05) ? "0" : number(rng, rng(1, 25));
        run(a, b);
    }
}

}
