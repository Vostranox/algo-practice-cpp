#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int k, int want) {
    check(Solution().kthSmallest(build_tree(root), k), want, "root", root, "k", k);
}

static void run_big(TreeNode* root, int k, int want, const string& label) {
    check(Solution().kthSmallest(root, k), want, "root", label, "k", k);
}

static TreeNode* balanced_bst(const vector<int>& vals, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = (lo + hi) / 2;
    TreeNode* node = new TreeNode(vals[mid]);
    node->left = balanced_bst(vals, lo, mid - 1);
    node->right = balanced_bst(vals, mid + 1, hi);
    return node;
}

static TreeNode* insert(TreeNode* root, int v) {
    TreeNode* child = new TreeNode(v);
    if (!root) return child;
    for (TreeNode* n = root;;) {
        TreeNode*& next = v < n->val ? n->left : n->right;
        if (!next) {
            next = child;
            return root;
        }
        n = next;
    }
}

TEST(examples) {
    run({6, 2, 8, 1, 4, 7, 9}, 3, 4);
    run({6, 2, 8, 1, 4, 7, 9}, 7, 9);
    run({3, 1, null, null, 2}, 2, 2);
}

TEST(edge_cases) {
    run({5}, 1, 5);
    run({2, 1}, 1, 1);
    run({2, 1}, 2, 2);
    run({1, null, 2}, 2, 2);
    run({0, null, 10000}, 1, 0);
    run({4, 3, null, 2, null, 1}, 1, 1);
    run({4, 3, null, 2, null, 1}, 4, 4);
    run({10, 5, 15, 3, 7, 12, 20, null, 4, 6}, 4, 6);
    run({10, 5, 15, 3, 7, 12, 20, null, 4, 6}, 2, 4);
    run({10, 5, 15, 3, 7, 12, 20, null, 4, 6}, 6, 10);
}

TEST(large) {
    const int n = 10000;
    Rng rng(57);
    vector<int> vals(n + 1);
    iota(vals.begin(), vals.end(), 0);
    vals.erase(vals.begin() + rng(0, n));
    TreeNode* root = balanced_bst(vals, 0, n - 1);
    vector<int> ks{1, n, n / 2, 2, n - 1};
    for (int i = 0; i < 20; ++i) {
        ks.push_back(rng(1, n));
    }
    for (int k : ks) {
        run_big(root, k, vals[k - 1], "balanced BST of 10^4 values from 0..10^4");
    }

    TreeNode* left = new TreeNode(n - 1);
    TreeNode* cur = left;
    for (int v = n - 2; v >= 0; --v) {
        cur = cur->left = new TreeNode(v);
    }
    for (int k : {1, n, 2, n / 2}) {
        run_big(left, k, k - 1, "left chain 9999, 9998, ..., 0");
    }

    TreeNode* right = new TreeNode(0);
    cur = right;
    for (int v = 1; v < n; ++v) {
        cur = cur->right = new TreeNode(v);
    }
    for (int k : {1, n, n - 1, n / 2}) {
        run_big(right, k, k - 1, "right chain 0, 1, ..., 9999");
    }
}

TEST(random) {
    Rng rng(570);
    for (int i = 0; i < 400; ++i) {
        vector<int> pool(51);
        iota(pool.begin(), pool.end(), 0);
        rng.shuffle(pool);
        pool.resize(rng(1, 30));
        TreeNode* t = nullptr;
        for (int v : pool) {
            t = insert(t, v);
        }
        int k = rng(1, static_cast<int>(pool.size()));
        run(tree_to_vec(t), k, sorted(pool)[k - 1]);
    }
}

}
