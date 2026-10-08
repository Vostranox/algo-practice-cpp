#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static vector<vector<char>> grid(const vector<string>& rows) {
    vector<vector<char>> g;
    for (auto& r : rows) {
        g.emplace_back(r.begin(), r.end());
    }
    return g;
}

static void run(vector<vector<char>> board, string word, bool want) {
    vector<vector<char>> arg = board;
    check(Solution().exist(arg, word), want, "board", board, "word", word);
}

static bool brute(const vector<vector<char>>& b, const string& word, vector<pair<int, int>>& path) {
    if (path.size() == word.size()) {
        for (size_t i = 1; i < path.size(); ++i) {
            if (abs(path[i].first - path[i - 1].first) + abs(path[i].second - path[i - 1].second) != 1) return false;
        }
        return true;
    }
    for (int r = 0; r < static_cast<int>(b.size()); ++r) {
        for (int c = 0; c < static_cast<int>(b[0].size()); ++c) {
            if (b[r][c] != word[path.size()] || find(path.begin(), path.end(), make_pair(r, c)) != path.end()) continue;
            path.emplace_back(r, c);
            bool ok = brute(b, word, path);
            path.pop_back();
            if (ok) return true;
        }
    }
    return false;
}

static const vector<string> BOARD = {"SEA", "TAR", "ONE"};

TEST(examples) {
    run(grid(BOARD), "STONE", true);
    run(grid(BOARD), "RATS", true);
    run(grid(BOARD), "TAT", false);
}

TEST(edge_cases) {
    run(grid({"a"}), "a", true);
    run(grid({"a"}), "A", false);
    run(grid({"a"}), "aa", false);
    run(grid({"AB", "CD"}), "ABDC", true);
    run(grid({"AB", "CD"}), "ABCD", false);
    run(grid({"AB", "CD"}), "ABA", false);
    run(grid({"AB", "CD"}), "ABDCA", false);
    run(grid({"HELLO"}), "OLLEH", true);
    run(grid({"HELLO"}), "HELO", false);
    run(grid({"x", "y", "z"}), "zyx", true);
    run(grid({"x", "y", "z"}), "xz", false);
    run(grid({"aA", "Aa"}), "aAa", true);
    run(grid({"aA", "Aa"}), "aa", false);
    run(grid(BOARD), "SEARENATO", true);
    run(grid(BOARD), "SEARENATS", false);
    vector<string> snake = {"ABCDEF", "LKJIHG", "MNOPQR", "XWVUTS", "YZabcd", "jihgfe"};
    run(grid(snake), "ABCDEFGHIJKLMNO", true);
    run(grid(snake), "ONMLKJIHGFEDCBA", true);
    run(grid(snake), "ABCDEFGHIJKLMNP", false);
}

TEST(uniform_boards) {
    vector<string> all_a(6, string(6, 'A'));
    run(grid(all_a), string(14, 'A') + "B", false);
    run(grid(all_a), string(15, 'A'), true);
    vector<string> corners = all_a;
    corners[0][0] = corners[5][5] = 'B';
    run(grid(corners), "B" + string(12, 'A') + "B", false);
    run(grid(corners), "B" + string(13, 'A') + "B", true);
    vector<string> one_b = all_a;
    one_b[0][0] = 'B';
    run(grid(one_b), string(14, 'A') + "B", true);
    run(grid(one_b), string(13, 'A') + "BB", false);
}

TEST(random) {
    Rng rng(79);
    vector<pair<int, int>> shapes = {{1, 4}, {2, 2}, {2, 3}, {3, 2}, {3, 3}, {1, 6}};
    for (int iter = 0; iter < 400; ++iter) {
        auto [m, n] = rng.pick(shapes);
        vector<string> rows;
        for (int r = 0; r < m; ++r) {
            rows.push_back(rng.str(n, "AB"));
        }
        string word = rng.str(rng(1, 6), "AB");
        auto board = grid(rows);
        vector<pair<int, int>> path;
        run(board, word, brute(board, word, path));
    }
}

}
