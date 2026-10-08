#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& p, const Tree& q, bool want) {
    check(Solution().isSameTree(build_tree(p), build_tree(q)), want, "p", p, "q", q);
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
    run({4, 7, 9}, {4, 7, 9}, true);
    run({4, 7}, {4, null, 7}, false);
    run({2, 1, 3}, {2, 3, 1}, false);
}

TEST(edge_cases) {
    run({}, {}, true);
    run({}, {0}, false);
    run({0}, {}, false);
    run({0}, {0}, true);
    run({-1}, {1}, false);
    run({1, 2, 3}, {1, 2}, false);
    run({1, null, 2}, {1, null, 2}, true);
    run({5, 5, 5, 5}, {5, 5, 5, null, 5}, false);
    run({3, 1, 4, 1, 5, 9, 2, 6}, {3, 1, 4, 1, 5, 9, 2, 6}, true);
    run({3, 1, 4, 1, 5, 9, 2, 6}, {3, 1, 4, 1, 5, 9, 2, 7}, false);
    run({10000, -10000}, {10000, -10000}, true);
}

TEST(random) {
    Rng rng(50);
    for (int i = 0; i < 600; ++i) {
        Tree p = tree_to_vec(random_tree(rng, rng(0, 100), -2, 2)), q;
        double r = rng.real();
        if (r < 0.4 || p.empty()) {
            q = p;
        } else if (r < 0.8) {
            TreeNode* t = build_tree(p);
            TreeNode* n = rng.pick(tree_nodes(t));
            int change = rng(0, 2);
            if (change == 0) {
                n->val += rng.coin() ? 1 : -1;
            } else if (change == 1) {
                swap(n->left, n->right);
            } else if (!n->left) {
                n->left = new TreeNode(0);
            }
            q = tree_to_vec(t);
        } else {
            q = tree_to_vec(random_tree(rng, rng(0, 100), -2, 2));
        }
        run(p, q, p == q);
    }
}

}
