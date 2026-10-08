#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, const vector<vector<int>>& want) {
    check(Solution().levelOrder(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, const vector<vector<int>>& want, const string& label) {
    check(Solution().levelOrder(root), want, "root", label);
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

static vector<vector<int>> by_depth(TreeNode* root) {
    vector<vector<int>> levels;
    walk(root, 0, levels);
    return levels;
}

TEST(examples) {
    run({8, 4, 12, null, 6, 10}, {{8}, {4, 12}, {6, 10}});
    run({1, 2, null, 3, null, 4}, {{1}, {2}, {3}, {4}});
    run({}, {});
}

TEST(edge_cases) {
    run({0}, {{0}});
    run({1, null, 2}, {{1}, {2}});
    run({5, 5, 5, -5, -5}, {{5}, {5, 5}, {-5, -5}});
    run({1, 2, 3, 4, 5, 6, 7}, {{1}, {2, 3}, {4, 5, 6, 7}});
    run({1, 2, 3, null, 4, 5, null, 6, null, null, 7}, {{1}, {2, 3}, {4, 5}, {6, 7}});
    run({-1000, null, 1000, 999, null, null, -999}, {{-1000}, {1000}, {999}, {-999}});
}

TEST(large) {
    Tree full(2000);
    for (int i = 0; i < 2000; ++i) {
        full[i] = i - 1000;
    }
    vector<vector<int>> want;
    for (int d = 0; (1 << d) - 1 < 2000; ++d) {
        want.emplace_back();
        for (int i = (1 << d) - 1; i < min((1 << (d + 1)) - 1, 2000); ++i) {
            want.back().push_back(i - 1000);
        }
    }
    run_big(build_tree(full), want, "complete tree with values -1000, -999, ..., 999 in level order");

    TreeNode* chain = new TreeNode(0);
    TreeNode* cur = chain;
    want = {{0}};
    for (int i = 1; i < 2000; ++i) {
        cur = cur->right = new TreeNode(i % 1000);
        want.push_back({i % 1000});
    }
    run_big(chain, want, "chain of 2000 right children");
}

TEST(random) {
    Rng rng(53);
    for (int i = 0; i < 300; ++i) {
        TreeNode* t = random_tree(rng, rng(0, rng.coin(0.05) ? 2000 : 50), -1000, 1000);
        run(tree_to_vec(t), by_depth(t));
    }
}

}
