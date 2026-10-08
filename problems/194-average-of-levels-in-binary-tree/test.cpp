#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

template <class Input>
static void verify(const vector<double>& got, const vector<double>& want, Input input) {
    for (size_t i = 0; i < max(got.size(), want.size()); ++i) {
        if (i < got.size() && i < want.size() && fabs(got[i] - want[i]) <= 1e-5 * max(1.0, fabs(want[i]))) continue;
        string msg = input() + "expected: " + clip(repr(want)) + "\ngot:      " + clip(repr(got));
        if (i < got.size() && i < want.size()) {
            msg += "\nproblem:  level " + to_string(i) + " (the root's level is 0): expected " + repr(want[i]) +
                   ", got " + repr(got[i]);
        } else {
            msg += "\nproblem:  expected " + to_string(want.size()) + " levels, got " + to_string(got.size());
        }
        fail(msg);
    }
}

static void run(const Tree& root, const vector<double>& want) {
    verify(Solution().averageOfLevels(build_tree(root)), want, [&] { return input_line("root", root); });
}

static void run_big(TreeNode* root, const vector<double>& want, const string& label) {
    verify(Solution().averageOfLevels(root), want, [&] { return input_line("root", label); });
}

static void walk(TreeNode* n, size_t depth, vector<pair<int64_t, int>>& levels) {
    if (!n) return;
    if (depth == levels.size()) {
        levels.emplace_back(0, 0);
    }
    levels[depth].first += n->val;
    levels[depth].second += 1;
    walk(n->left, depth + 1, levels);
    walk(n->right, depth + 1, levels);
}

static vector<double> averages(TreeNode* root) {
    vector<pair<int64_t, int>> levels;
    walk(root, 0, levels);
    vector<double> out;
    for (auto [sum, count] : levels) {
        out.push_back(static_cast<double>(sum) / count);
    }
    return out;
}

static TreeNode* random_tree(Rng& rng, int n, int64_t lo, int64_t hi) {
    TreeNode* root = new TreeNode(static_cast<int>(rng.range(lo, hi)));
    vector<TreeNode**> slots{&root->left, &root->right};
    for (int i = 1; i < n; ++i) {
        swap(slots[rng.next() % slots.size()], slots.back());
        TreeNode** s = slots.back();
        slots.pop_back();
        *s = new TreeNode(static_cast<int>(rng.range(lo, hi)));
        slots.push_back(&(*s)->left);
        slots.push_back(&(*s)->right);
    }
    return root;
}

TEST(examples) {
    run({4, 2, 9, null, null, 5, 8}, {4, 5.5, 6.5});
    run({-3, 10, -7, 1}, {-3, 1.5, 1});
    run({2147483647, 2147483647, 2147483647}, {2147483647, 2147483647});
}

TEST(edge_cases) {
    run({0}, {0});
    run({-7}, {-7});
    run({1, 2}, {1, 2});
    run({1, null, 2}, {1, 2});
    run({1, 2, 3, 4, 5, 6, 7}, {1, 2.5, 5.5});
    run({1, 2, null, 4, 5}, {1, 2, 4.5});
    run({0, 1, 2, 1, 1, 2}, {0, 1.5, 4.0 / 3});
    run({0, -1, -2}, {0, -1.5});
    run({INT_MIN, INT_MIN, INT_MIN}, {-2147483648.0, -2147483648.0});
    run({INT_MAX, INT_MIN}, {2147483647, -2147483648.0});
    run({1, INT_MAX, INT_MIN}, {1, -0.5});
    run({1, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, {1, 2147483647, 2147483647});
    run({5, 1, 2, 3}, {5, 1.5, 3});
}

TEST(large) {
    const int n = 10000;
    vector<double> want_max;
    for (int d = 0; d < 14; ++d) {
        want_max.push_back(2147483647);
    }
    run_big(build_tree(Tree(n, INT_MAX)), want_max, "complete tree with 10^4 nodes, all 2^31 - 1");
    vector<double> want_min(14, -2147483648.0);
    run_big(build_tree(Tree(n, INT_MIN)), want_min, "complete tree with 10^4 nodes, all -2^31");

    TreeNode* chain = new TreeNode(INT_MIN);
    TreeNode* cur = chain;
    vector<double> want_chain{-2147483648.0};
    for (int i = 1; i < n; ++i) {
        int v = i % 2 ? INT_MAX : INT_MIN + i;
        cur = cur->right = new TreeNode(v);
        want_chain.push_back(v);
    }
    run_big(chain, want_chain, "chain of 10^4 right children, alternating 2^31 - 1 and about -2^31");

    Rng rng(194);
    for (int i = 0; i < 3; ++i) {
        TreeNode* t = random_tree(rng, n, i == 2 ? INT_MAX - 1000 : INT_MIN, INT_MAX);
        run_big(t, averages(t), "random tree with 10^4 nodes");
    }
    Tree full(n);
    for (auto& v : full) {
        v = static_cast<int>(rng.range(INT_MIN, INT_MAX));
    }
    TreeNode* t = build_tree(full);
    run_big(t, averages(t), "complete tree with 10^4 random values");
}

TEST(random) {
    Rng rng(1940);
    for (int i = 0; i < 400; ++i) {
        TreeNode* t = i % 2 ? random_tree(rng, rng(1, 30), -10, 10) : random_tree(rng, rng(1, 30), INT_MIN, INT_MAX);
        run(tree_to_vec(t), averages(t));
    }
}

}
