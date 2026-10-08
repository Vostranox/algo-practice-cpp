#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static TreeNode* balanced_bst(const vector<int>& vals, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = (lo + hi) / 2;
    return new TreeNode(vals[mid], balanced_bst(vals, lo, mid - 1), balanced_bst(vals, mid + 1, hi));
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

static vector<int> distinct_sorted(Rng& rng, int n) {
    vector<int> vals(n);
    int width = 1000000 / n;
    for (int i = 0; i < n; ++i) {
        vals[i] = i * width + rng(0, width - 1);
    }
    return vals;
}

template <class Label>
static void drive(TreeNode* root, const vector<int>& vals, Rng& rng, int calls, double p_has, const Label& label) {
    Trace t("BSTIterator", label);
    BSTIterator it(root);
    size_t pos = 0;
    for (int i = 0; i < calls; ++i) {
        if (pos == vals.size() || rng.coin(p_has)) {
            EXPECT_CALL(t, pos < vals.size(), it, hasNext);
        } else {
            EXPECT_CALL(t, vals[pos++], it, next);
        }
    }
}

TEST(example) {
    Tree vals{8, 4, 10, null, 6, null, 12};
    Trace t("BSTIterator", vals);
    BSTIterator it(build_tree(vals));
    EXPECT_CALL(t, 4, it, next);
    EXPECT_CALL(t, 6, it, next);
    EXPECT_CALL(t, true, it, hasNext);
    EXPECT_CALL(t, 8, it, next);
    EXPECT_CALL(t, 10, it, next);
    EXPECT_CALL(t, 12, it, next);
    EXPECT_CALL(t, false, it, hasNext);
}

TEST(edge_cases) {
    {
        Tree vals{0};
        Trace t("BSTIterator", vals);
        BSTIterator it(build_tree(vals));
        EXPECT_CALL(t, true, it, hasNext);
        EXPECT_CALL(t, true, it, hasNext);
        EXPECT_CALL(t, 0, it, next);
        EXPECT_CALL(t, false, it, hasNext);
        EXPECT_CALL(t, false, it, hasNext);
    }
    {
        Tree vals{1000000, 999999, null, 5};
        Trace t("BSTIterator", vals);
        BSTIterator it(build_tree(vals));
        EXPECT_CALL(t, 5, it, next);
        EXPECT_CALL(t, true, it, hasNext);
        EXPECT_CALL(t, 999999, it, next);
        EXPECT_CALL(t, 1000000, it, next);
        EXPECT_CALL(t, false, it, hasNext);
    }
    {
        Tree vals{1, null, 2, null, 3};
        Trace t("BSTIterator", vals);
        BSTIterator it(build_tree(vals));
        EXPECT_CALL(t, 1, it, next);
        EXPECT_CALL(t, 2, it, next);
        EXPECT_CALL(t, true, it, hasNext);
        EXPECT_CALL(t, 3, it, next);
        EXPECT_CALL(t, false, it, hasNext);
    }
    {
        Tree vals{50, 20, 80, 10, 40, 60, null, null, 15, 30, null, null, 70};
        Trace t("BSTIterator", vals);
        BSTIterator it(build_tree(vals));
        for (int v : {10, 15, 20, 30, 40, 50, 60, 70, 80}) {
            EXPECT_CALL(t, true, it, hasNext);
            EXPECT_CALL(t, v, it, next);
        }
        EXPECT_CALL(t, false, it, hasNext);
    }
    {
        Tree vals{3, 1, 4, null, 2};
        Trace t("BSTIterator", vals);
        BSTIterator it(build_tree(vals));
        for (int v : {1, 2, 3, 4}) {
            EXPECT_CALL(t, v, it, next);
        }
    }
}

TEST(two_iterators) {
    Tree vals{4, 2, 6, 1, 3, 5, 7};
    TreeNode* root = build_tree(vals);
    Trace t("BSTIterator", vals);
    BSTIterator a(root);
    EXPECT_CALL(t, 1, a, next);
    EXPECT_CALL(t, 2, a, next);
    t.add("BSTIterator", vals);
    BSTIterator b(root);
    EXPECT_CALL(t, 1, b, next);
    EXPECT_CALL(t, 3, a, next);
    EXPECT_CALL(t, 2, b, next);
    for (int v : {4, 5, 6, 7}) {
        EXPECT_CALL(t, v, a, next);
    }
    EXPECT_CALL(t, false, a, hasNext);
    EXPECT_CALL(t, true, b, hasNext);
    EXPECT_CALL(t, 3, b, next);
}

TEST(large) {
    Rng rng(191);
    const int n = 100000;
    vector<int> vals = distinct_sorted(rng, n);

    TreeNode* left = new TreeNode(vals[n - 1]);
    TreeNode* cur = left;
    for (int i = n - 2; i >= 0; --i) {
        cur = cur->left = new TreeNode(vals[i]);
    }
    drive(left, vals, rng, n, 0.25, string("left chain of 10^5 nodes"));

    TreeNode* right = new TreeNode(vals[0]);
    cur = right;
    for (int i = 1; i < n; ++i) {
        cur = cur->right = new TreeNode(vals[i]);
    }
    drive(right, vals, rng, n, 0.25, string("right chain of 10^5 nodes"));

    drive(balanced_bst(vals, 0, n - 1), vals, rng, n, 0.25, string("balanced BST of 10^5 nodes"));

    vector<int> half = distinct_sorted(rng, n / 2);
    TreeNode* random_bst = nullptr;
    vector<int> order = half;
    rng.shuffle(order);
    for (int v : order) {
        random_bst = insert(random_bst, v);
    }
    drive(random_bst, half, rng, n, 0.5, string("random BST of 5 * 10^4 nodes"));
}

TEST(random) {
    Rng rng(1910);
    for (int i = 0; i < 300; ++i) {
        vector<int> vals = distinct_sorted(rng, rng(1, 30));
        vector<int> order = vals;
        rng.shuffle(order);
        TreeNode* root = nullptr;
        for (int v : order) {
            root = insert(root, v);
        }
        drive(root, vals, rng, 2 * static_cast<int>(vals.size()) + 2, 0.4, tree_to_vec(root));
    }
}

}
