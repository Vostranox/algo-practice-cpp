#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, bool want) {
    check(Solution().isSymmetric(build_tree(root)), want, "root", root);
}

static TreeNode* mirrored(const TreeNode* n) {
    return n ? new TreeNode(n->val, mirrored(n->right), mirrored(n->left)) : nullptr;
}

static bool brute(TreeNode* root) { return tree_to_vec(root) == tree_to_vec(mirrored(root)); }

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

static TreeNode* symmetric_tree(Rng& rng, int half, int lo, int hi) {
    TreeNode* left = random_tree(rng, half, lo, hi);
    return new TreeNode(rng(lo, hi), left, mirrored(left));
}

TEST(examples) {
    run({4, 7, 7, 1, 9, 9, 1}, true);
    run({4, 7, 7, null, 9, null, 9}, false);
    run({1, 2, 2, 2, null, 2}, false);
}

TEST(edge_cases) {
    run({0}, true);
    run({1, 2}, false);
    run({1, null, 2}, false);
    run({1, 2, 2}, true);
    run({1, 2, 3}, false);
    run({1, 2, 2, null, 3, 3}, true);
    run({1, 2, 2, 3, null, null, 3}, true);
    run({1, 2, 2, 3, 4, 3, 4}, false);
    run({1, 2, 2, 3, 4, 4, 3}, true);
    run({1, 2, 2, 3, null, 3}, false);
    run({-100, 100, 100}, true);
    run({-1, -2, -2, -3, null, null, -3}, true);
    run({5, 4, 4, 3, null, null, 3, 2, null, null, 2}, true);
    run({5, 4, 4, 3, null, null, 3, 2, null, 2}, false);
    run({5, 4, 4, 3, null, null, 3, 2, null, null, 1}, false);
    run({1, 2, 2, null, 3, null, 3}, false);
}

TEST(large) {
    Rng rng(185);
    for (int i = 0; i < 6; ++i) {
        TreeNode* t = symmetric_tree(rng, 499, -100, 100);
        run(tree_to_vec(t), true);
        vector<TreeNode*> right = tree_nodes(t->right);
        TreeNode* n = right[rng(0, static_cast<int>(right.size()) - 1)];
        if (i % 3 == 0) {
            n->val = n->val == 100 ? -100 : n->val + 1;
        } else if (i % 3 == 1) {
            TreeNode* leaf = right.back();
            (rng.coin() ? leaf->left : leaf->right) = new TreeNode(0);
        } else {
            while (tree_to_vec(n->left) == tree_to_vec(n->right)) {
                n = rng.pick(right);
            }
            swap(n->left, n->right);
        }
        run(tree_to_vec(t), false);
    }
    TreeNode* root = new TreeNode(0);
    TreeNode *a = root, *b = root;
    for (int i = 1; i <= 499; ++i) {
        a = a->left = new TreeNode(i % 201 - 100);
        b = b->right = new TreeNode(i % 201 - 100);
    }
    run(tree_to_vec(root), true);
    b->val = -b->val + 1;
    run(tree_to_vec(root), false);
}

TEST(random) {
    Rng rng(1850);
    for (int i = 0; i < 600; ++i) {
        TreeNode* t;
        if (i % 3 == 0) {
            t = random_tree(rng, rng(1, 12), 0, 1);
        } else {
            t = symmetric_tree(rng, rng(0, 12), -2, 2);
            if (i % 3 == 2 && t->left) {
                vector<TreeNode*> nodes = tree_nodes(t);
                TreeNode* n = rng.pick(nodes);
                int what = rng(0, 2);
                if (what == 0) {
                    n->val = rng(-2, 2);
                } else if (what == 1) {
                    swap(n->left, n->right);
                } else if (!n->left) {
                    n->left = new TreeNode(rng(-2, 2));
                } else if (!n->right) {
                    n->right = new TreeNode(rng(-2, 2));
                }
            }
        }
        run(tree_to_vec(t), brute(t));
    }
}

}
