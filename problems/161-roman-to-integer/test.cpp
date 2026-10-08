#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static string roman(int n) {
    static const char* thousands[] = {"", "M", "MM", "MMM"};
    static const char* hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    static const char* tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    static const char* ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    return string(thousands[n / 1000]) + hundreds[n / 100 % 10] + tens[n / 10 % 10] + ones[n % 10];
}

static int value(const string& s) {
    static const map<char, int> letter = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    int total = 0, biggest = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        int v = letter.at(s[i]);
        total += v < biggest ? -v : v;
        biggest = max(biggest, v);
    }
    return total;
}

static void run(const string& s, int want) { check(Solution().romanToInt(s), want, "s", s); }

TEST(examples) {
    run("VIII", 8);
    run("XLIX", 49);
    run("MMCDXXI", 2421);
}

TEST(edge_cases) {
    run("I", 1);
    run("III", 3);
    run("IV", 4);
    run("V", 5);
    run("IX", 9);
    run("XL", 40);
    run("XC", 90);
    run("CD", 400);
    run("CM", 900);
    run("M", 1000);
    run("LVIII", 58);
    run("XCIX", 99);
    run("CDXLIV", 444);
    run("CDXCIX", 499);
    run("DCCC", 800);
    run("CMXCIX", 999);
    run("MDCLXVI", 1666);
    run("MCMXCIV", 1994);
    run("MMXXVI", 2026);
    run("MMMDCCCLXXXVIII", 3888);
    run("MMMCMXCIX", 3999);
}

TEST(all_numbers) {
    for (int n = 1; n <= 3999; ++n) {
        string s = roman(n);
        ensure(value(s) == n, "the test's two oracles disagree (a bug in the test)", "n", n, "numeral", s);
        run(s, n);
    }
}

}
