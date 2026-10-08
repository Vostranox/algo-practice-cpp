#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, const Tree& want) {
    check(tree_to_vec(Solution().invertTree(build_tree(root))), want, "root", root);
}

static TreeNode* mirrored(const TreeNode* n) {
    return n ? new TreeNode(n->val, mirrored(n->right), mirrored(n->left)) : nullptr;
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

TEST(examples) {
    run({5, 3, 8, 1, 4, 7, 9}, {5, 8, 3, 9, 7, 4, 1});
    run({2, 1, null, 0}, {2, null, 1, null, 0});
    run({}, {});
}

TEST(edge_cases) {
    run({7}, {7});
    run({1, 2}, {1, null, 2});
    run({1, null, 2}, {1, 2});
    run({-1, -2, -3}, {-1, -3, -2});
    run({0, 0, 0, null, 0}, {0, 0, 0, null, null, 0});
    run({4, 2, 7, 1, 3, 6, 9, null, null, null, null, 5}, {4, 7, 2, 9, 6, 3, 1, null, null, null, 5});
    run({1, 2, null, 3, null, 4}, {1, null, 2, null, 3, null, 4});
    run({-100, 100, -100}, {-100, -100, 100});
}

TEST(random) {
    Rng rng(46);
    for (int i = 0; i < 500; ++i) {
        TreeNode* t = random_tree(rng, rng(1, 100), -100, 100);
        run(tree_to_vec(t), tree_to_vec(mirrored(t)));
    }
}

}
