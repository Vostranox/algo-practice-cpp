#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Board = vector<vector<char>>;

static Board make_board(const vector<string>& rows) {
    Board b;
    for (auto& r : rows) {
        b.emplace_back(r.begin(), r.end());
    }
    return b;
}

static void run(const Board& board, const vector<string>& words, const vector<string>& want) {
    Board b = board;
    vector<string> w = words;
    vector<string> got = Solution().findWords(b, w);
    ensure(!has_duplicates(got), "every found word must be listed only once", "board", board, "words", words,
           "got", got);
    check(sorted(got), sorted(want), "board", board, "words", words);
}

static bool traceable(const Board& board, const string& word) {
    int R = board.size(), C = board[0].size();
    vector<vector<bool>> used(R, vector<bool>(C));
    function<bool(int, int, size_t)> dfs = [&](int r, int c, size_t i) {
        if (r < 0 || c < 0 || r >= R || c >= C || used[r][c] || board[r][c] != word[i]) return false;
        if (i + 1 == word.size()) return true;
        used[r][c] = true;
        bool ok = dfs(r + 1, c, i + 1) || dfs(r - 1, c, i + 1) || dfs(r, c + 1, i + 1) || dfs(r, c - 1, i + 1);
        used[r][c] = false;
        return ok;
    };
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (dfs(r, c, 0)) return true;
        }
    }
    return false;
}

TEST(examples) {
    run(make_board({"cat", "roe", "dgs"}), {"cat", "goes", "roe", "dog", "toe", "cart", "sea"}, {"cat", "goes", "roe"});
    run(make_board({"ab", "cd"}), {"abdc", "abcd", "acdb"}, {"abdc", "acdb"});
    run(make_board({"xyx"}), {"xyx", "xyxy"}, {"xyx"});
}

TEST(edge_cases) {
    run(make_board({"a"}), {"a", "aa", "b"}, {"a"});
    run(make_board({"z"}), {"y"}, {});
    run(make_board({"ab"}), {"aba", "ab", "ba", "bab", "b"}, {"ab", "ba", "b"});
    run(make_board({"aa", "aa"}), {"aaaa", "aaaaa", "aa"}, {"aaaa", "aa"});
    run(make_board({"a", "b", "c", "d"}), {"abcd", "dcba", "ac", "bcd"}, {"abcd", "dcba", "bcd"});
    run(make_board({"ab", "cd"}), {"a", "ab", "abd", "abdc", "abdca"}, {"a", "ab", "abd", "abdc"});
}

TEST(random) {
    Rng rng(212);
    for (int t = 0; t < 300; ++t) {
        int R = rng(1, 4), C = rng(1, 4);
        string alpha = rng.coin() ? "ab" : "abc";
        Board board(R, vector<char>(C));
        for (auto& row : board) {
            for (auto& ch : row) {
                ch = alpha[rng(0, alpha.size() - 1)];
            }
        }
        set<string> ws;
        int n = rng(1, 25);
        while (static_cast<int>(ws.size()) < n) {
            ws.insert(rng.str(rng(1, 7), alpha));
        }
        vector<string> words(ws.begin(), ws.end());
        rng.shuffle(words);
        vector<string> want;
        for (auto& w : words) {
            if (traceable(board, w)) {
                want.push_back(w);
            }
        }
        run(board, words, want);
    }
}

TEST(large) {
    Rng rng(2120);
    const int R = 12, C = 12;
    const string specials = "bcdefghijklm";
    Board board(R, vector<char>(C, 'a'));
    vector<pair<int, int>> spots;
    while (spots.size() < specials.size()) {
        int r = rng(0, R - 1), c = rng(0, C - 1);
        bool ok = true;
        for (auto [r2, c2] : spots) {
            ok &= abs(r - r2) + abs(c - c2) >= 2;
        }
        if (ok) {
            spots.push_back({r, c});
        }
    }
    for (size_t i = 0; i < spots.size(); ++i) {
        board[spots[i].first][spots[i].second] = specials[i];
    }

    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    set<string> found;
    while (found.size() < 500) {
        int len = rng(1, 10);
        vector<pair<int, int>> path{{rng(0, R - 1), rng(0, C - 1)}};
        string w(1, board[path[0].first][path[0].second]);
        while (static_cast<int>(w.size()) < len) {
            vector<pair<int, int>> next;
            for (int d = 0; d < 4; ++d) {
                int r = path.back().first + dr[d], c = path.back().second + dc[d];
                if (r >= 0 && c >= 0 && r < R && c < C && find(path.begin(), path.end(), pair{r, c}) == path.end()) {
                    next.push_back({r, c});
                }
            }
            if (next.empty()) break;
            path.push_back(rng.pick(next));
            w += board[path.back().first][path.back().second];
        }
        if (!w.starts_with("aaaaaaaaa")) {
            found.insert(w);
        }
    }

    unordered_set<string> missing;
    auto add_missing = [&](int p) {
        string pool = specials;
        for (int i = 0; i < 5; ++i) {
            swap(pool[i], pool[rng(i, static_cast<int>(pool.size()) - 1)]);
        }
        string w = string(p, 'a') + pool[0] + pool[1];
        int room = 10 - static_cast<int>(w.size());
        int extra = room > 0 && rng.coin(0.3) ? rng(0, room - 1) : room;
        for (int i = 0, next = 2; i < extra; ++i) {
            w += rng.coin() ? 'a' : pool[next++];
        }
        return missing.insert(w).second;
    };
    for (auto [p, count] : {pair{8, 100}, pair{7, 1000}, pair{6, 8000}}) {
        for (int made = 0; made < count;) {
            made += add_missing(p);
        }
    }
    while (found.size() + missing.size() < 30000) {
        add_missing(5);
    }

    vector<string> words(found.begin(), found.end());
    words.insert(words.end(), missing.begin(), missing.end());
    rng.shuffle(words);
    run(board, words, vector<string>(found.begin(), found.end()));
}

}
