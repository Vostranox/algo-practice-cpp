#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int want) {
    check(Solution().goodNodes(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, int want, const string& label) {
    check(Solution().goodNodes(root), want, "root", label);
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

static int brute(TreeNode* root) {
    unordered_map<TreeNode*, TreeNode*> parent;
    vector<TreeNode*> nodes = tree_nodes(root);
    for (auto* n : nodes) {
        for (auto* c : {n->left, n->right}) {
            if (c) {
                parent[c] = n;
            }
        }
    }
    int count = 0;
    for (auto* n : nodes) {
        bool good = true;
        for (TreeNode* a = n; parent.count(a);) {
            a = parent[a];
            if (a->val > n->val) {
                good = false;
            }
        }
        count += good;
    }
    return count;
}

template <class F>
static TreeNode* broom(F f, int g) {
    TreeNode* root = new TreeNode(f(0));
    TreeNode* cur = root;
    for (int i = 1; i < 10000; ++i) {
        cur = cur->left = new TreeNode(f(i));
    }
    cur->left = build_tree(Tree(90000, g));
    return root;
}

TEST(examples) {
    run({5, 2, 8, 6, 1, 7, 9}, 4);
    run({4, 4, null, 4, 3}, 3);
    run({-7}, 1);
}

TEST(edge_cases) {
    run({0}, 1);
    run({-5, -10, -3}, 2);
    run({3, 3, 3}, 3);
    run({1, null, 2, null, 3}, 3);
    run({3, 2, null, 1}, 1);
    run({2, null, 4, 10, 8, null, null, 4}, 4);
    run({1, 10, 2, null, null, 3}, 4);
    run({10000, -10000, 10000}, 2);
    run({-10000, -10000, -10000, -10000}, 4);
}

TEST(large) {
    const int n = 100000;
    Tree vals(n);
    int even = 0;
    for (int i = 0; i < n; ++i) {
        int level = bit_width(static_cast<unsigned>(i + 1)) - 1;
        vals[i] = level % 2 ? -level : level;
        even += level % 2 == 0;
    }
    run_big(build_tree(vals), even, "complete tree of 10^5 nodes, value = level on even levels, -level on odd");
    run_big(build_tree(Tree(n, 7)), n, "complete tree of 10^5 equal values");
    run_big(broom([](int i) { return -10000 + i / 5; }, -10000 + 9999 / 5), n,
            "chain of 10^4 non-decreasing values -10000, ..., -10000, -9999, ..., -8001, then 9*10^4 more -8001s");
    run_big(broom([](int i) { return i == 0 ? 10000 : 9999 - i; }, -10000), 1,
            "chain 10000, 9998, 9997, ..., 0, then 9*10^4 nodes with -10000");
    run_big(broom([](int i) { return i % 2 ? 3 : 7; }, 3), 5000, "chain 7, 3, 7, 3, ... (10^4 nodes), then 9*10^4 threes");
}

TEST(random) {
    Rng rng(55);
    for (int i = 0; i < 400; ++i) {
        TreeNode* t = random_tree(rng, rng(1, 40), -5, 5);
        run(tree_to_vec(t), brute(t));
    }
}

}
