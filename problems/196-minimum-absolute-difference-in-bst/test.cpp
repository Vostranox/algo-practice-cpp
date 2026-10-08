#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int want) {
    check(Solution().getMinimumDifference(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, int want, const string& label) {
    check(Solution().getMinimumDifference(root), want, "root", label);
}

static int min_gap(vector<int> vals) {
    sort(vals.begin(), vals.end());
    int best = INT_MAX;
    for (size_t i = 1; i < vals.size(); ++i) {
        best = min(best, vals[i] - vals[i - 1]);
    }
    return best;
}

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

static vector<int> distinct(Rng& rng, int n, int hi) {
    vector<int> out;
    unordered_set<int> seen;
    while (static_cast<int>(out.size()) < n) {
        int v = rng(0, hi);
        if (seen.insert(v).second) {
            out.push_back(v);
        }
    }
    return out;
}

TEST(examples) {
    run({50, 20, 80, null, 48}, 2);
    run({6, 2, 9, 1, 4}, 1);
    run({0, null, 100000}, 100000);
}

TEST(edge_cases) {
    run({1, 0}, 1);
    run({100000, 0}, 100000);
    run({5, 3, 8, null, 4, 7}, 1);
    run({10, 5, 30, null, null, 11}, 1);
    run({10, 5, 30, null, 9, 11}, 1);
    run({100, 50, 150, 25, 75, 125, 175}, 25);
    run({40, 20, 60, 10, 30, 50, 70, null, null, null, 39}, 1);
    run({1, null, 3, 2}, 1);
    run({90000, 0, null, null, 89999}, 1);
    run({4, 2, 6, 1, 3, 5, 7}, 1);
    run({0, null, 50000, null, 100000}, 50000);
}

TEST(large) {
    Rng rng(196);
    const int n = 10000;
    for (int i = 0; i < 3; ++i) {
        vector<int> vals = distinct(rng, n, 100000);
        vector<int> s = sorted(vals);
        run_big(balanced_bst(s, 0, n - 1), min_gap(vals), "balanced BST of 10^4 random values");
        TreeNode* t = nullptr;
        for (int v : vals) {
            t = insert(t, v);
        }
        run_big(t, min_gap(vals), "10^4 random values inserted into a BST");
    }
    vector<int> tens(n);
    for (int i = 0; i < n; ++i) {
        tens[i] = 10 * i;
    }
    run_big(balanced_bst(tens, 0, n - 1), 10, "balanced BST of 0, 10, ..., 99990");
    tens[7777] = tens[7778] - 3;
    run_big(balanced_bst(tens, 0, n - 1), 3, "balanced BST of 0, 10, ..., 99990, with 77770 changed to 77777");
    tens[n / 2 - 1] = tens[n / 2 - 2] + 2;
    run_big(balanced_bst(tens, 0, n - 1), 2, "balanced BST of 0, 10, ..., 99990, 77770 -> 77777, root 49990 -> 49982");

    TreeNode* right = new TreeNode(0);
    TreeNode* cur = right;
    for (int i = 1; i < n; ++i) {
        cur = cur->right = new TreeNode(i < n - 1 ? 10 * i : 10 * (n - 2) + 1);
    }
    run_big(right, 1, "right chain 0, 10, 20, ..., 99980, 99981");
    TreeNode* left = new TreeNode(100000);
    cur = left;
    for (int i = 1; i < n; ++i) {
        cur = cur->left = new TreeNode(100000 - 10 * i);
    }
    run_big(left, 10, "left chain 100000, 99990, ..., 10");
}

TEST(random) {
    Rng rng(1960);
    for (int i = 0; i < 400; ++i) {
        vector<int> vals = distinct(rng, rng(2, 30), i % 2 ? 60 : 100000);
        TreeNode* t = nullptr;
        for (int v : vals) {
            t = insert(t, v);
        }
        run(tree_to_vec(t), min_gap(vals));
    }
}

}
