#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, bool want) {
    check(Solution().isValidBST(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, bool want, const string& label) {
    check(Solution().isValidBST(root), want, "root", label);
}

static bool brute(TreeNode* root) {
    for (auto* n : tree_nodes(root)) {
        for (auto* x : tree_nodes(n->left)) {
            if (x->val >= n->val) return false;
        }
        for (auto* x : tree_nodes(n->right)) {
            if (x->val <= n->val) return false;
        }
    }
    return true;
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
    run({8, 3, 10, 1, 6}, true);
    run({8, 3, 10, 1, 9}, false);
    run({5, null, 5}, false);
}

TEST(edge_cases) {
    run({1}, true);
    run({2, 1, 3}, true);
    run({2, 3, 1}, false);
    run({1, 1}, false);
    run({5, 4, 6, null, null, 3, 7}, false);
    run({3, 1, 5, 0, 4}, false);
    run({10, 5, 15, null, null, 12, 20}, true);
    run({32, 26, 47, 19, null, null, 56, null, 27}, false);
    run({-3, -7, 0, null, -5, -1, 4}, true);
}

TEST(int_limits) {
    run({INT_MIN}, true);
    run({INT_MAX}, true);
    run({INT_MIN, null, INT_MAX}, true);
    run({INT_MAX, INT_MIN}, true);
    run({0, INT_MIN, INT_MAX}, true);
    run({INT_MAX, null, INT_MAX}, false);
    run({INT_MIN, INT_MIN}, false);
    run({INT_MAX, INT_MAX}, false);
    run({INT_MIN, null, INT_MIN}, false);
    run({0, INT_MIN, INT_MAX, null, INT_MIN + 1, INT_MAX - 1}, true);
}

TEST(large) {
    const int n = 10000;
    TreeNode* chain = new TreeNode(0);
    TreeNode* cur = chain;
    for (int i = 1; i < n; ++i) {
        cur = cur->right = new TreeNode(i);
    }
    run_big(chain, true, "right chain 0, 1, ..., 9999");
    cur->val = n - 2;
    run_big(chain, false, "right chain 0, 1, ..., 9998, 9998");

    TreeNode* top = new TreeNode(1);
    TreeNode* node = top;
    for (int i = 1; i < n; ++i) {
        int v = i % 2 ? n - i / 2 : 1 + i / 2;
        TreeNode* child = new TreeNode(v);
        (v > node->val ? node->right : node->left) = child;
        node = child;
    }
    run_big(top, true, "zigzag 1 -> 10000 -> 2 -> 9999 -> ... -> 5000 -> 5001");
    node->left = new TreeNode(n / 2 - 1);
    run_big(top, false, "same zigzag plus a left child 4999 under the last node 5001");

    Rng rng(56);
    vector<int> vals{INT_MIN, INT_MAX};
    unordered_set<int> seen(vals.begin(), vals.end());
    while (static_cast<int>(vals.size()) < n) {
        int v = static_cast<int>(rng.range(INT_MIN, INT_MAX));
        if (seen.insert(v).second) {
            vals.push_back(v);
        }
    }
    sort(vals.begin(), vals.end());
    TreeNode* root = balanced_bst(vals, 0, n - 1);
    run_big(root, true, "balanced BST of 10^4 values including INT_MIN and INT_MAX");
    vector<TreeNode*> nodes = tree_nodes(root);
    swap(nodes[n - 1]->val, nodes[n - 2]->val);
    run_big(root, false, "same tree with the values of two bottom leaves swapped");
}

TEST(random) {
    Rng rng(5600);
    for (int i = 0; i < 400; ++i) {
        TreeNode* t = nullptr;
        if (rng.coin()) {
            vector<int> pool(41);
            iota(pool.begin(), pool.end(), -20);
            rng.shuffle(pool);
            for (int k = rng(1, 12); k > 0; --k) {
                t = insert(t, pool[k]);
            }
            if (rng.coin()) {
                rng.pick(tree_nodes(t))->val = rng(-20, 20);
            }
        } else {
            Tree vals{rng(-3, 3)};
            for (int k = rng(0, 12); k > 0; --k) {
                if (rng.coin(0.8)) {
                    vals.push_back(rng(-3, 3));
                } else {
                    vals.push_back(null);
                }
            }
            t = build_tree(vals);
        }
        run(tree_to_vec(t), brute(t));
    }
}

}
