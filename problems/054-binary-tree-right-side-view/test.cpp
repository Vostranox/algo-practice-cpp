#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, const vector<int>& want) {
    check(Solution().rightSideView(build_tree(root)), want, "root", root);
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

static vector<int> last_per_level(TreeNode* root) {
    vector<vector<int>> levels;
    walk(root, 0, levels);
    vector<int> out;
    for (auto& level : levels) {
        out.push_back(level.back());
    }
    return out;
}

TEST(examples) {
    run({7, 3, 9, 1, 5, null, null, null, null, 4}, {7, 9, 5, 4});
    run({2, null, 6, null, 8}, {2, 6, 8});
    run({}, {});
}

TEST(edge_cases) {
    run({0}, {0});
    run({1, 2}, {1, 2});
    run({1, 2, 3, 4}, {1, 3, 4});
    run({1, 2, 3, null, 5, null, null, 6}, {1, 3, 5, 6});
    run({1, 2, null, 3, null, 4}, {1, 2, 3, 4});
    run({-1, -2, -3, -4, -5, -6, -7}, {-1, -3, -7});
    run({5, 5, 5, 5, null, null, 5}, {5, 5, 5});
    run({1, 2, 3, 4, null, null, null, 8, 9}, {1, 3, 4, 9});
}

TEST(random) {
    Rng rng(54);
    for (int i = 0; i < 600; ++i) {
        TreeNode* t = random_tree(rng, rng(0, 100), -100, 100);
        run(tree_to_vec(t), last_per_level(t));
    }
}

}
