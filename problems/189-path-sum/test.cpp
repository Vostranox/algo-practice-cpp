#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int targetSum, bool want) {
    check(Solution().hasPathSum(build_tree(root), targetSum), want, "root", root, "targetSum", targetSum);
}

static void run_big(TreeNode* root, int targetSum, bool want, const string& label) {
    check(Solution().hasPathSum(root, targetSum), want, "root", label, "targetSum", targetSum);
}

static void path_sums(TreeNode* n, int64_t sum, set<int64_t>& leaf_sums, set<int64_t>& inner_sums) {
    if (!n) return;
    sum += n->val;
    if (!n->left && !n->right) {
        leaf_sums.insert(sum);
        return;
    }
    inner_sums.insert(sum);
    path_sums(n->left, sum, leaf_sums, inner_sums);
    path_sums(n->right, sum, leaf_sums, inner_sums);
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

static vector<int> interesting_targets(Rng& rng, TreeNode* t) {
    set<int64_t> leaf_sums, inner_sums;
    path_sums(t, 0, leaf_sums, inner_sums);
    vector<int> out;
    for (auto* s : {&leaf_sums, &inner_sums}) {
        vector<int64_t> v(s->begin(), s->end());
        for (int k = 0; k < 3 && !v.empty(); ++k) {
            int64_t x = rng.pick(v);
            if (-1000 <= x && x <= 1000) {
                out.push_back(static_cast<int>(x));
            }
        }
    }
    for (int k = 0; k < 3; ++k) {
        out.push_back(rng(-1000, 1000));
    }
    return out;
}

static void run_random(Rng& rng, TreeNode* t, const string& label) {
    set<int64_t> leaf_sums, inner_sums;
    path_sums(t, 0, leaf_sums, inner_sums);
    for (int target : interesting_targets(rng, t)) {
        bool want = leaf_sums.count(target) > 0;
        if (label.empty()) {
            run(tree_to_vec(t), target, want);
        } else {
            run_big(t, target, want, label);
        }
    }
}

TEST(examples) {
    run({3, 9, -2, null, null, 6, 1}, 7, true);
    run({3, 9, -2, null, null, 6, 1}, 1, false);
    run({}, 0, false);
}

TEST(edge_cases) {
    run({1}, 1, true);
    run({1}, 0, false);
    run({0}, 0, true);
    run({-1000}, -1000, true);
    run({1, 2}, 1, false);
    run({1, 2}, 3, true);
    run({1, null, 2}, 1, false);
    run({1, null, 2}, 3, true);
    run({1, 2, 3}, 3, true);
    run({1, 2, 3}, 4, true);
    run({1, 2, 3}, 1, false);
    run({1, 2, 3}, 6, false);
    run({-2, null, -3}, -5, true);
    run({5, -10, 3, 7, null, null, -2}, 2, true);
    run({5, -10, 3, 7, null, null, -2}, 6, true);
    run({5, -10, 3, 7, null, null, -2}, 8, false);
    run({5, -10, 3, 7, null, null, -2}, -5, false);
    run({2, 2, null, 2, null, 2}, 8, true);
    run({2, 2, null, 2, null, 2}, 6, false);
    run({1000, -1000, 1000}, 0, true);
    run({1000, 1000}, 1000, false);
    run({0, 0, 0, 0, null, null, 0}, 0, true);
}

TEST(large) {
    TreeNode* chain = new TreeNode(0);
    TreeNode* cur = chain;
    for (int i = 1; i < 5000; ++i) {
        cur = cur->left = new TreeNode(i % 2 ? 1000 : -1000);
    }
    run_big(chain, 1000, true, "left chain 0, 1000, -1000, 1000, ..., 1000 (5000 nodes)");
    run_big(chain, 0, false, "left chain 0, 1000, -1000, 1000, ..., 1000 (5000 nodes)");
    cur->val = -1000;
    run_big(chain, 1000, false, "left chain 0, 1000, -1000, ..., 1000, -1000 (5000 nodes)");
    run_big(chain, -1000, true, "left chain 0, 1000, -1000, ..., 1000, -1000 (5000 nodes)");

    Rng rng(189);
    Tree full(5000);
    for (auto& v : full) {
        v = rng(-80, 80);
    }
    run_random(rng, build_tree(full), "complete tree with 5000 random values in [-80, 80]");
    for (int i = 0; i < 3; ++i) {
        run_random(rng, random_tree(rng, 5000, -1000, 1000), "random tree with 5000 nodes");
    }
    run_random(rng, random_tree(rng, 5000, -3, 3), "random tree with 5000 nodes, values in [-3, 3]");
}

TEST(random) {
    Rng rng(1890);
    for (int i = 0; i < 300; ++i) {
        TreeNode* t = random_tree(rng, rng(1, 20), i % 2 ? -5 : -1000, i % 2 ? 5 : 1000);
        run_random(rng, t, "");
    }
    for (int target : {0, 7, -3}) {
        run({}, target, false);
    }
}

}
