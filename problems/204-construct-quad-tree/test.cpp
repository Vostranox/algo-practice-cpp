#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static string serialize(QuadNode* root) {
    vector<string> out;
    deque<QuadNode*> q{root};
    while (!q.empty() && out.size() < 300) {
        QuadNode* n = q.front();
        q.pop_front();
        if (!n) {
            out.push_back("null");
            continue;
        }
        out.push_back("[" + to_string(n->isLeaf) + ", " + to_string(n->val) + "]");
        for (QuadNode* c : {n->topLeft, n->topRight, n->bottomLeft, n->bottomRight}) {
            q.push_back(c);
        }
    }
    bool more = any_of(q.begin(), q.end(), [](QuadNode* n) { return n != nullptr; });
    while (!out.empty() && out.back() == "null") {
        out.pop_back();
    }
    string s;
    for (auto& x : out) {
        s += (s.empty() ? "" : ", ") + x;
    }
    return "[" + s + (more ? ", ...]" : "]");
}

static string check_region(QuadNode* node, const vector<vector<int>>& grid, int r, int c, int size) {
    string where = "rows " + to_string(r) + ".." + to_string(r + size - 1) + ", cols " + to_string(c) + ".." +
                   to_string(c + size - 1);
    if (!node) return "the node for " + where + " is missing (nullptr)";
    int ones = 0;
    for (int i = r; i < r + size; ++i) {
        for (int j = c; j < c + size; ++j) {
            ones += grid[i][j];
        }
    }
    if (ones == 0 || ones == size * size) {
        int v = ones ? 1 : 0;
        if (!node->isLeaf) return "the node for " + where + " must be a leaf: all its cells are " + to_string(v);
        if (node->val != (v == 1)) {
            return "the leaf for " + where + " has val " + (node->val ? "true" : "false") + ", but all its cells are " +
                   to_string(v);
        }
        if (node->topLeft || node->topRight || node->bottomLeft || node->bottomRight) {
            return "the leaf for " + where + " must have four nullptr children";
        }
        return "";
    }
    if (node->isLeaf) return "the node for " + where + " is a leaf, but that region holds both 0s and 1s";
    int h = size / 2;
    for (string s : {check_region(node->topLeft, grid, r, c, h), check_region(node->topRight, grid, r, c + h, h),
                     check_region(node->bottomLeft, grid, r + h, c, h),
                     check_region(node->bottomRight, grid, r + h, c + h, h)}) {
        if (!s.empty()) return s;
    }
    return "";
}

template <class Input>
static void verify(const vector<vector<int>>& grid, Input input) {
    vector<vector<int>> arg = grid;
    QuadNode* got = Solution().construct(arg);
    string problem = check_region(got, grid, 0, 0, static_cast<int>(grid.size()));
    if (!problem.empty()) {
        fail(input() + "problem:  " + problem + "\ngot:      " + clip(serialize(got)));
    }
}

static void run(const vector<vector<int>>& grid) {
    verify(grid, [&] { return input_line("grid", grid); });
}

static void run_big(const vector<vector<int>>& grid, const string& label) {
    verify(grid, [&] { return input_line("grid", label); });
}

static void run_exact(const vector<vector<int>>& grid, const string& want) {
    run(grid);
    vector<vector<int>> arg = grid;
    QuadNode* got = Solution().construct(arg);
    vector<QuadNode*> all{got};
    for (size_t i = 0; i < all.size() && all.size() < 10000; ++i) {
        for (QuadNode* c : {all[i]->topLeft, all[i]->topRight, all[i]->bottomLeft, all[i]->bottomRight}) {
            if (c) {
                all.push_back(c);
            }
        }
    }
    for (QuadNode* n : all) {
        if (!n->isLeaf) {
            n->val = false;
        }
    }
    check(serialize(got), want, "grid", grid);
}

static void fill(vector<vector<int>>& g, Rng& rng, int r, int c, int size, double p_leaf) {
    if (size == 1 || rng.coin(p_leaf)) {
        int v = rng(0, 1);
        for (int i = r; i < r + size; ++i) {
            for (int j = c; j < c + size; ++j) {
                g[i][j] = v;
            }
        }
        return;
    }
    int h = size / 2;
    fill(g, rng, r, c, h, p_leaf);
    fill(g, rng, r, c + h, h, p_leaf);
    fill(g, rng, r + h, c, h, p_leaf);
    fill(g, rng, r + h, c + h, h, p_leaf);
}

static vector<vector<int>> structured(Rng& rng, int n, double p_leaf) {
    vector<vector<int>> g(n, vector<int>(n));
    fill(g, rng, 0, 0, n, p_leaf);
    return g;
}

TEST(examples) {
    run_exact({{1, 1}, {1, 1}}, "[[1, 1]]");
    run_exact({{1, 0}, {0, 1}}, "[[0, 0], [1, 1], [1, 0], [1, 0], [1, 1]]");
    run_exact({{1, 1, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 1}},
              "[[0, 0], [1, 1], [1, 0], [1, 1], [0, 0], null, null, null, null, null, null, null, null, null, "
              "null, null, null, [1, 0], [1, 1], [1, 1], [1, 1]]");
}

TEST(edge_cases) {
    run_exact({{0}}, "[[1, 0]]");
    run_exact({{1}}, "[[1, 1]]");
    run_exact({{0, 0}, {0, 0}}, "[[1, 0]]");
    run_exact({{1, 1}, {1, 0}}, "[[0, 0], [1, 1], [1, 1], [1, 1], [1, 0]]");
    run_exact({{0, 1}, {0, 0}}, "[[0, 0], [1, 0], [1, 1], [1, 0], [1, 0]]");
    run_exact({{0, 0}, {1, 0}}, "[[0, 0], [1, 0], [1, 0], [1, 1], [1, 0]]");
    run_exact({{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}, "[[1, 1]]");
    run_exact({{0, 0, 1, 1}, {0, 0, 1, 1}, {1, 1, 0, 0}, {1, 1, 0, 0}}, "[[0, 0], [1, 0], [1, 1], [1, 1], [1, 0]]");
    run_exact({{1, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}},
              "[[0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [1, 1], [1, 1], [1, 1], [1, 0], [1, 1], [1, 1], [1, 0], "
              "[1, 1], [1, 1], [1, 0], [1, 1], [1, 1], [1, 0], [1, 1], [1, 1], [1, 1]]");
    run({{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}});
    vector<vector<int>> one(8, vector<int>(8, 0));
    one[7][7] = 1;
    run(one);
    one[7][7] = 0, one[0][0] = 1;
    run(one);
}

TEST(large) {
    run_big(vector<vector<int>>(64, vector<int>(64, 0)), "64 x 64, all 0");
    run_big(vector<vector<int>>(64, vector<int>(64, 1)), "64 x 64, all 1");
    vector<vector<int>> board(64, vector<int>(64));
    for (int i = 0; i < 64; ++i) {
        for (int j = 0; j < 64; ++j) {
            board[i][j] = (i + j) % 2;
        }
    }
    run_big(board, "64 x 64 checkerboard");
    vector<vector<int>> almost(64, vector<int>(64, 1));
    almost[37][21] = 0;
    run_big(almost, "64 x 64, all 1 except grid[37][21] = 0");
    Rng rng(204);
    for (double p : {0.15, 0.3, 0.5}) {
        run_big(structured(rng, 64, p), "64 x 64 random grid with uniform blocks");
    }
    vector<vector<int>> noise(64, vector<int>(64));
    for (auto& row : noise) {
        for (auto& x : row) {
            x = rng.coin(0.9);
        }
    }
    run_big(noise, "64 x 64 random grid, 90% ones");
}

TEST(random) {
    Rng rng(2040);
    for (int i = 0; i < 300; ++i) {
        int n = 1 << rng(0, 4);
        run(structured(rng, n, rng.real() * 0.6));
    }
}

}
