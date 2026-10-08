#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static const string NASTY = "#0123456789,:;|/\\\"' \n\r\t\0\x01-[]{}()é中😀 "s;

static string encode(const vector<string>& strs) {
    vector<string> arg = strs;
    return Codec().encode(arg);
}

static void roundtrip(const vector<string>& strs) {
    string enc = encode(strs);
    vector<string> dec = Codec().decode(enc);
    check(dec, strs, "strs", strs, "encoded", enc);
}

TEST(examples) {
    roundtrip({"neet", "code", "love", "you"});
    roundtrip({"", "a#b", "3#", "x,y"});
    roundtrip({});
}

TEST(empty_strings) {
    roundtrip({""});
    roundtrip({"", ""});
    roundtrip({"", "", ""});
    roundtrip({"a", ""});
    roundtrip({"", "a"});
}

TEST(delimiter_like_content) {
    roundtrip({"#"});
    roundtrip({"##", "#", "#3#"});
    roundtrip({"4#abcd", "0#", "12#"});
    roundtrip({"1", "22", "333", "10"});
    roundtrip({"a,b", ",", ",,"});
    roundtrip({"line1\nline2", "\n", "\r\n"});
    roundtrip({"key:value", ":", "::"});
    roundtrip({"|", "\\", "\\|", "\"quoted\"", "'"});
    roundtrip({"\0"s, "a\0b"s, "\t", "\0\0"s});
    roundtrip({"   ", " "});
    roundtrip({"é", "中文", "😀😀", " x "});
    roundtrip({"\xff", "\x80\xfe", string(200, '\xff')});
    roundtrip({"[]", "[\"a\", \"b\"]", "{}"});
    roundtrip({NASTY, string(NASTY.rbegin(), NASTY.rend())});
}

TEST(independent_calls) {
    vector<string> a = {"first", "list"}, b = {"second", "", "#"};
    string ea = encode(a), eb = encode(b);
    check(Codec().decode(eb), b, "strs", b, "encoded", eb);
    check(Codec().decode(ea), a, "strs", a, "encoded", ea);
    string ec = encode({});
    check(Codec().decode(ea), a, "strs", a, "encoded", ea);
    check(Codec().decode(ec), vector<string>{}, "strs", vector<string>{}, "encoded", ec);
}

TEST(random) {
    string all_bytes;
    for (int c = 0; c < 256; ++c) {
        all_bytes += char(c);
    }
    Rng rng(8);
    for (int i = 0; i < 300; ++i) {
        vector<string> strs(rng(0, 6));
        for (auto& s : strs) {
            s = rng.str(rng(0, 6), rng.coin() ? NASTY + "ab" : all_bytes);
        }
        roundtrip(strs);
    }
    vector<string> big(200);
    for (auto& s : big) {
        s = rng.str(200, all_bytes);
    }
    roundtrip(big);
    roundtrip(vector<string>(200, string(200, '9')));
    roundtrip(vector<string>(200, ""));
}

}
