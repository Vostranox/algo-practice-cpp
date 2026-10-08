#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, bool want) {
    check(Solution().isBalanced(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, bool want, const string& label) {
    check(Solution().isBalanced(root), want, "root", label);
}

static TreeNode* fib_tree(int h) {
    return h <= 0 ? nullptr : new TreeNode(h, fib_tree(h - 1), fib_tree(h - 2));
}

static TreeNode* perfect(int h) { return build_tree(Tree((1 << h) - 1, 7)); }

static int height(TreeNode* n) { return n ? 1 + max(height(n->left), height(n->right)) : 0; }

static bool brute_balanced(TreeNode* root) {
    for (auto* n : tree_nodes(root)) {
        if (abs(height(n->left) - height(n->right)) > 1) return false;
    }
    return true;
}

static TreeNode* random_balanced(Rng& rng, int h) {
    if (h <= 0) return nullptr;
    int pick = rng(0, 2);
    int hl = pick == 2 ? h - 2 : h - 1, hr = pick == 1 ? h - 2 : h - 1;
    TreeNode* node = new TreeNode(rng(-5, 5));
    node->left = random_balanced(rng, hl);
    node->right = random_balanced(rng, hr);
    return node;
}

TEST(examples) {
    run({10, 5, 15, 2, 8, null, 20}, true);
    run({1, 2, 3, 4, null, null, 6, 5, null, null, 7}, false);
    run({}, true);
}

TEST(edge_cases) {
    run({1}, true);
    run({1, 2}, true);
    run({1, null, 2}, true);
    run({1, 2, null, 3}, false);
    run({1, null, 2, null, 3}, false);
    run({1, 2, 3, 4}, true);
    run({1, 2, 3, 4, null, null, null, 5}, false);
    run({1, 2, 2, 3, 3, null, null, 4, 4}, false);
    run({-3, -3, -3, -3, -3, -3, -3, -3, null, null, -3}, true);
    run(tree_to_vec(fib_tree(5)), true);
    run({1, 2, 3, 4, 5, 6, 7, 8, null, 10, null, 12, 13, null, null, 9}, false);
}

TEST(large) {
    run_big(build_tree(Tree(5000, 0)), true, "complete tree with 5000 nodes");
    TreeNode* chain = new TreeNode(1);
    TreeNode* cur = chain;
    for (int i = 1; i < 5000; ++i) {
        cur = cur->left = new TreeNode(1);
    }
    run_big(chain, false, "chain of 5000 left children");
    run_big(fib_tree(17), true, "minimal balanced (Fibonacci) tree of height 17, 4180 nodes");

    for (int extra : {1, 2}) {
        TreeNode* root = new TreeNode(0, perfect(11), perfect(11));
        TreeNode* leaf = root->left;
        while (leaf->left) {
            leaf = leaf->left;
        }
        for (int i = 0; i < extra; ++i) {
            leaf = leaf->left = new TreeNode(1);
        }
        leaf = root->right;
        while (leaf->right) {
            leaf = leaf->right;
        }
        leaf->right = new TreeNode(2);
        run_big(root, extra == 1, "two perfect height-11 subtrees, a " + to_string(extra) +
                                      "-node chain under the leftmost leaf, one child under the rightmost leaf");
    }
}

TEST(random) {
    Rng rng(49);
    for (int i = 0; i < 400; ++i) {
        TreeNode* t;
        if (i % 2) {
            t = random_balanced(rng, rng(1, 6));
            for (int k = rng(0, 2); k > 0; --k) {
                TreeNode* n = rng.pick(tree_nodes(t));
                if (!n->left) {
                    n->left = new TreeNode(0);
                } else if (!n->right) {
                    n->right = new TreeNode(0);
                }
            }
        } else {
            Tree vals(rng(0, 20));
            for (auto& v : vals) {
                if (rng.coin(0.75)) {
                    v = rng(0, 1);
                }
            }
            t = build_tree(vals);
        }
        run(tree_to_vec(t), brute_balanced(t));
    }
}

}
