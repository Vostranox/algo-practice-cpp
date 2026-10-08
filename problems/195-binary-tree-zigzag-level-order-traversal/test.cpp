#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, const vector<vector<int>>& want) {
    check(Solution().zigzagLevelOrder(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, const vector<vector<int>>& want, const string& label) {
    check(Solution().zigzagLevelOrder(root), want, "root", label);
}

static TreeNode* random_tree(Rng& rng, int n, int lo, int hi) {
    if (n == 0) return nullptr;
    TreeNode* root = new TreeNode(rng(lo, hi));
    vector<TreeNode**> slots{&root->left, &root->right};
    for (int i = 1; i < n; ++i) {
        swap(slots[rng.next() % slots.size()], slots.back());
        TreeNode** s = slots.back();
        slots.pop_back();
        *s = new TreeNode(rng(lo, hi));
        slots.push_back(&(*s)->left);
        slots.push_back(&(*s)->right);
    }
    return root;
}

static void walk(TreeNode* node, size_t depth, vector<vector<int>>& levels) {
    if (!node) return;
    if (depth == levels.size()) {
        levels.emplace_back();
    }
    levels[depth].push_back(node->val);
    walk(node->left, depth + 1, levels);
    walk(node->right, depth + 1, levels);
}

static vector<vector<int>> zigzag(TreeNode* root) {
    vector<vector<int>> levels;
    walk(root, 0, levels);
    for (size_t d = 1; d < levels.size(); d += 2) {
        reverse(levels[d].begin(), levels[d].end());
    }
    return levels;
}

TEST(examples) {
    run({8, 4, 12, null, 6, 10, 14}, {{8}, {12, 4}, {6, 10, 14}});
    run({1, 2, 3, 4, 5, 6, 7, 8, 9}, {{1}, {3, 2}, {4, 5, 6, 7}, {9, 8}});
    run({}, {});
}

TEST(edge_cases) {
    run({0}, {{0}});
    run({1, 2}, {{1}, {2}});
    run({1, null, 2}, {{1}, {2}});
    run({1, 2, 3}, {{1}, {3, 2}});
    run({1, 2, null, 3, null, 4}, {{1}, {2}, {3}, {4}});
    run({1, 2, 3, null, 4, 5, null, 6, null, null, 7}, {{1}, {3, 2}, {4, 5}, {7, 6}});
    run({-100, 100, -100, 50, null, null, -50}, {{-100}, {-100, 100}, {50, -50}});
    run({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        {{1}, {3, 2}, {4, 5, 6, 7}, {15, 14, 13, 12, 11, 10, 9, 8}});
    run({5, 5, 5, 5, 5, 5, 5, 5, 6}, {{5}, {5, 5}, {5, 5, 5, 5}, {6, 5}});
    run({3, 9, 20, null, null, 15, 7, 1, 2, 4}, {{3}, {20, 9}, {15, 7}, {4, 2, 1}});
}

TEST(large) {
    Tree full(2000);
    for (int i = 0; i < 2000; ++i) {
        full[i] = i % 201 - 100;
    }
    vector<vector<int>> want;
    for (int d = 0; (1 << d) - 1 < 2000; ++d) {
        want.emplace_back();
        for (int i = (1 << d) - 1; i < min((1 << (d + 1)) - 1, 2000); ++i) {
            want.back().push_back(i % 201 - 100);
        }
        if (d % 2) {
            reverse(want.back().begin(), want.back().end());
        }
    }
    run_big(build_tree(full), want, "complete tree with values (i % 201) - 100 in level order");

    TreeNode* chain = new TreeNode(0);
    TreeNode* cur = chain;
    want = {{0}};
    for (int i = 1; i < 2000; ++i) {
        cur = (i % 3 ? cur->right : cur->left) = new TreeNode(i % 100);
        want.push_back({i % 100});
    }
    run_big(chain, want, "chain of 2000 nodes");

    Rng rng(195);
    for (int i = 0; i < 3; ++i) {
        TreeNode* t = random_tree(rng, 2000, -100, 100);
        run_big(t, zigzag(t), "random tree with 2000 nodes");
    }
}

TEST(random) {
    Rng rng(1950);
    for (int i = 0; i < 300; ++i) {
        TreeNode* t = random_tree(rng, rng(0, 50), -100, 100);
        run(tree_to_vec(t), zigzag(t));
    }
}

}
