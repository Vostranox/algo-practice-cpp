#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int want) {
    check(Solution().maxDepth(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, int want, const string& label) {
    check(Solution().maxDepth(root), want, "root", label);
}

static TreeNode* chain(int n, const string& sides) {
    TreeNode* root = new TreeNode(0);
    TreeNode* cur = root;
    for (int i = 1; i < n; ++i) {
        TreeNode* child = new TreeNode(i % 100);
        (sides[i % sides.size()] == 'L' ? cur->left : cur->right) = child;
        cur = child;
    }
    return root;
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

static int bfs_levels(TreeNode* root) {
    vector<TreeNode*> level;
    if (root) {
        level.push_back(root);
    }
    int depth = 0;
    while (!level.empty()) {
        ++depth;
        vector<TreeNode*> next;
        for (auto* n : level) {
            for (auto* c : {n->left, n->right}) {
                if (c) {
                    next.push_back(c);
                }
            }
        }
        level = next;
    }
    return depth;
}

TEST(examples) {
    run({4, 2, 6, null, 3, 5}, 3);
    run({1, null, 2, null, 3, null, 4}, 4);
    run({}, 0);
}

TEST(edge_cases) {
    run({0}, 1);
    run({1, 2}, 2);
    run({1, null, 2}, 2);
    run({-5, -5, -5}, 2);
    run({1, 2, 3, 4, null, null, null, 5}, 4);
    run({1, 2, 3, null, null, null, 4, 5}, 4);
    run({1, 2, 3, 4, 5, 6, 7}, 3);
}

TEST(large) {
    Tree full(10000);
    for (int i = 0; i < 10000; ++i) {
        full[i] = i % 100;
    }
    run_big(build_tree(full), 14, "complete tree with 10^4 nodes");
    run_big(chain(10000, "L"), 10000, "chain of 10^4 left children");
    run_big(chain(10000, "R"), 10000, "chain of 10^4 right children");
    run_big(chain(10000, "LR"), 10000, "zigzag chain of 10^4 nodes");
}

TEST(random) {
    Rng rng(47);
    for (int i = 0; i < 500; ++i) {
        TreeNode* t = random_tree(rng, rng(0, 60), -100, 100);
        run(tree_to_vec(t), bfs_levels(t));
    }
}

}
