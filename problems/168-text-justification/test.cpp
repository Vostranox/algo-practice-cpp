#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<string> words, int maxWidth, vector<string> want) {
    vector<string> arg = words;
    check(Solution().fullJustify(arg, maxWidth), want, "words", words, "maxWidth", maxWidth);
}

static vector<string> oracle(const vector<string>& words, int width) {
    vector<vector<string>> lines{{}};
    int used = 0;
    for (const string& w : words) {
        if (!lines.back().empty() && used + 1 + static_cast<int>(w.size()) > width) {
            lines.push_back({}), used = 0;
        }
        used += (lines.back().empty() ? 0 : 1) + w.size();
        lines.back().push_back(w);
    }
    vector<string> out;
    for (size_t li = 0; li < lines.size(); ++li) {
        const auto& ws = lines[li];
        vector<int> gap(ws.size() - 1, 1);
        int total = -1;
        for (const string& w : ws) {
            total += w.size() + 1;
        }
        bool justify = li + 1 < lines.size() && ws.size() > 1;
        for (size_t k = 0; justify && total < width; k = (k + 1) % gap.size()) {
            ++gap[k], ++total;
        }
        string line = ws[0];
        for (size_t k = 1; k < ws.size(); ++k) {
            line += string(gap[k - 1], ' ') + ws[k];
        }
        out.push_back(line + string(width - line.size(), ' '));
    }
    return out;
}

TEST(examples) {
    run({"We", "hold", "these", "truths", "to", "be", "self-evident"}, 14,
        {"We  hold these", "truths  to  be", "self-evident  "});
    run({"extraordinary", "is", "it"}, 14, {"extraordinary ", "is it         "});
}

TEST(edge_cases) {
    run({"one"}, 3, {"one"});
    run({"one"}, 7, {"one    "});
    run({"a"}, 1, {"a"});
    run({"a", "b"}, 1, {"a", "b"});
    run({"a", "b", "c"}, 5, {"a b c"});
    run({"x", "y", "z", "w", "v"}, 11, {"x y z w v  "});
    run({"a", "bb", "ccc"}, 5, {"a  bb", "ccc  "});
    run({"ab", "c", "d", "e", "fgh"}, 8, {"ab c d e", "fgh     "});
    run({"sit", "amet,", "consectetur"}, 11, {"sit   amet,", "consectetur"});
    run({"To", "be,", "or", "not", "to", "be:", "that", "is", "the", "question."}, 12,
        {"To   be,  or", "not  to  be:", "that  is the", "question.   "});
    run({"aaaa", "bb", "cc", "dd", "eeee"}, 15, {"aaaa  bb  cc dd", "eeee           "});
    run({"one", "two", "three", "four"}, 100, {"one two three four" + string(82, ' ')});
}

TEST(random) {
    Rng rng(168);
    for (int i = 0; i < 400; ++i) {
        int width = rng(1, 12);
        vector<string> words(rng(1, 10));
        for (auto& w : words) {
            w = rng.str(rng(1, min(width, 4)), "ab.!");
        }
        run(words, width, oracle(words, width));
    }
}

TEST(large) {
    Rng rng(1680);
    for (int width : {20, 21, 37, 100}) {
        vector<string> words(300);
        for (auto& w : words) {
            w = rng.str(rng(1, 20), "abcdefghijklmnopqrstuvwxyzABCXYZ.,;:!?'-");
        }
        run(words, width, oracle(words, width));
    }
    vector<string> words(300, string(20, 'w'));
    run(words, 20, vector<string>(300, string(20, 'w')));
    vector<string> ones(300, "i");
    run(ones, 100, oracle(ones, 100));
}

}
