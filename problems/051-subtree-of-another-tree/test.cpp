#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, const Tree& sub, bool want) {
    check(Solution().isSubtree(build_tree(root), build_tree(sub)), want, "root", root, "subRoot", sub);
}

static void run_big(TreeNode* root, TreeNode* sub, bool want, const string& label) {
    check(Solution().isSubtree(root, sub), want, "trees", label);
}

static TreeNode* random_tree(Rng& rng, int n, int lo, int hi) {
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

static bool brute(TreeNode* root, TreeNode* sub) {
    Tree want = tree_to_vec(sub);
    for (auto* n : tree_nodes(root)) {
        if (tree_to_vec(n) == want) return true;
    }
    return false;
}

static TreeNode* left_chain(const vector<int>& vals) {
    TreeNode* root = new TreeNode(vals[0]);
    TreeNode* cur = root;
    for (size_t i = 1; i < vals.size(); ++i) {
        cur = cur->left = new TreeNode(vals[i]);
    }
    return root;
}

static vector<int> ones_then(int ones, optional<int> last) {
    vector<int> v(ones, 1);
    if (last) {
        v.push_back(*last);
    }
    return v;
}

TEST(examples) {
    run({5, 3, 8, 1, 4}, {3, 1, 4}, true);
    run({5, 3, 8, 1, 4, null, null, null, null, 2}, {3, 1, 4}, false);
    run({1, 1}, {1}, true);
}

TEST(edge_cases) {
    run({7}, {7}, true);
    run({7}, {8}, false);
    run({1, 2, 3}, {1, 2, 3}, true);
    run({1, 2}, {1}, false);
    run({1, null, 2}, {2}, true);
    run({1, 2, 3}, {1, 2}, false);
    run({1, 2, 3}, {2, 3}, false);
    run({12}, {2}, false);
    run({2, 22}, {2}, false);
    run({-2}, {2}, false);
    run({3, 4, -2}, {2}, false);
    run({3, 4, -2}, {-2}, true);
    run({1, 2, null, 3}, {2, 3}, true);
    run({1, 2, null, 3}, {2, null, 3}, false);
    run({4, 4, null, 4, 4}, {4, 4}, false);
    run({4, 4, 4, null, null, null, 4}, {4, null, 4}, true);
}

TEST(large) {
    run_big(left_chain(ones_then(1999, 2)), left_chain(ones_then(999, 2)), true,
            "root = left chain of 1999 ones then a 2, subRoot = left chain of 999 ones then a 2");
    run_big(left_chain(ones_then(2000, {})), left_chain(ones_then(999, 2)), false,
            "root = left chain of 2000 ones, subRoot = left chain of 999 ones then a 2");
    run_big(left_chain(ones_then(2000, {})), left_chain(ones_then(1000, {})), true,
            "root = left chain of 2000 ones, subRoot = left chain of 1000 ones");
    run_big(build_tree(Tree(2000, 0)), build_tree(Tree(7, 0)), true,
            "root = complete tree of 2000 zeros, subRoot = perfect tree of 7 zeros");
    run_big(build_tree(Tree(2000, 0)), build_tree(Tree(1000, 0)), false,
            "root = complete tree of 2000 zeros, subRoot = complete tree of 1000 zeros");
}

TEST(random) {
    Rng rng(51);
    for (int i = 0; i < 500; ++i) {
        TreeNode* root = random_tree(rng, rng(1, 30), 0, 2);
        TreeNode* sub;
        double r = rng.real();
        if (r < 0.7) {
            sub = build_tree(tree_to_vec(rng.pick(tree_nodes(root))));
            if (r >= 0.4) {
                TreeNode* n = rng.pick(tree_nodes(sub));
                if (rng.coin()) {
                    n->val = rng(0, 2);
                } else if (!n->left) {
                    n->left = new TreeNode(rng(0, 2));
                }
            }
        } else {
            sub = random_tree(rng, rng(1, 4), 0, 2);
        }
        run(tree_to_vec(root), tree_to_vec(sub), brute(root, sub));
    }
}

}
