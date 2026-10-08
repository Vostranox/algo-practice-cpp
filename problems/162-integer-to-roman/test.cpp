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

static void run(int num, const string& want) { check(Solution().intToRoman(num), want, "num", num); }

TEST(examples) {
    run(68, "LXVIII");
    run(49, "XLIX");
    run(2894, "MMDCCCXCIV");
}

TEST(edge_cases) {
    run(1, "I");
    run(3, "III");
    run(4, "IV");
    run(5, "V");
    run(9, "IX");
    run(10, "X");
    run(40, "XL");
    run(90, "XC");
    run(400, "CD");
    run(900, "CM");
    run(1000, "M");
    run(58, "LVIII");
    run(99, "XCIX");
    run(444, "CDXLIV");
    run(499, "CDXCIX");
    run(800, "DCCC");
    run(999, "CMXCIX");
    run(1666, "MDCLXVI");
    run(1994, "MCMXCIV");
    run(2026, "MMXXVI");
    run(3000, "MMM");
    run(3888, "MMMDCCCLXXXVIII");
    run(3999, "MMMCMXCIX");
}

TEST(all_numbers) {
    for (int n = 1; n <= 3999; ++n) {
        string want = roman(n);
        ensure(value(want) == n, "the test's two oracles disagree (a bug in the test)", "n", n, "numeral", want);
        run(n, want);
    }
}

}
