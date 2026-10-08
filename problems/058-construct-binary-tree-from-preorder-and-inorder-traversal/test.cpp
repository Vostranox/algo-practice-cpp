#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& preorder, const vector<int>& inorder, const Tree& want) {
    vector<int> pre = preorder, in = inorder;
    check(tree_to_vec(Solution().buildTree(pre, in)), want, "preorder", preorder, "inorder", inorder);
}

static void preorder_of(TreeNode* n, vector<int>& out) {
    if (!n) return;
    out.push_back(n->val);
    preorder_of(n->left, out);
    preorder_of(n->right, out);
}

static void inorder_of(TreeNode* n, vector<int>& out) {
    if (!n) return;
    inorder_of(n->left, out);
    out.push_back(n->val);
    inorder_of(n->right, out);
}

static void run_tree(TreeNode* t) {
    vector<int> pre, in;
    preorder_of(t, pre);
    inorder_of(t, in);
    run(pre, in, tree_to_vec(t));
}

static TreeNode* random_tree(Rng& rng, int n) {
    vector<int> pool(6001);
    iota(pool.begin(), pool.end(), -3000);
    rng.shuffle(pool);
    TreeNode* root = new TreeNode(pool[0]);
    vector<TreeNode**> slots{&root->left, &root->right};
    for (int i = 1; i < n; ++i) {
        swap(slots[rng.next() % slots.size()], slots.back());
        TreeNode** s = slots.back();
        slots.pop_back();
        *s = new TreeNode(pool[i]);
        slots.push_back(&(*s)->left);
        slots.push_back(&(*s)->right);
    }
    return root;
}

static TreeNode* chain(int n, const string& sides) {
    TreeNode* root = new TreeNode(1);
    TreeNode* cur = root;
    for (int i = 1; i < n; ++i) {
        TreeNode* child = new TreeNode(i + 1);
        (sides[i % sides.size()] == 'L' ? cur->left : cur->right) = child;
        cur = child;
    }
    return root;
}

TEST(examples) {
    run({10, 4, 2, 6, 15, 20}, {2, 4, 6, 10, 15, 20}, {10, 4, 15, 2, 6, null, 20});
    run({1, 2, 3}, {3, 2, 1}, {1, 2, null, 3});
    run({-1}, {-1}, {-1});
}

TEST(edge_cases) {
    run({1, 2, 3}, {1, 2, 3}, {1, null, 2, null, 3});
    run({1, 2}, {2, 1}, {1, 2});
    run({1, 2}, {1, 2}, {1, null, 2});
    run({5, -3, 8, 0, 7}, {-3, 5, 0, 8, 7}, {5, -3, 8, null, null, 0, 7});
    run({1, 2, 4, 5, 3, 6, 7}, {4, 2, 5, 1, 6, 3, 7}, {1, 2, 3, 4, 5, 6, 7});
    run({3000, -3000}, {-3000, 3000}, {3000, -3000});
    run({1, 2, 3, 4}, {2, 4, 3, 1}, {1, 2, null, null, 3, 4});
    run({0, 1, 2}, {1, 0, 2}, {0, 1, 2});
}

TEST(large) {
    Rng rng(58);
    run_tree(random_tree(rng, 3000));
    run_tree(chain(3000, "L"));
    run_tree(chain(3000, "R"));
    run_tree(chain(3000, "LR"));
    run_tree(chain(3000, "LLR"));
    Tree full(3000);
    for (int i = 0; i < 3000; ++i) {
        full[i] = 1500 - i;
    }
    run_tree(build_tree(full));
}

TEST(random) {
    Rng rng(580);
    for (int i = 0; i < 400; ++i) {
        run_tree(random_tree(rng, rng(1, 25)));
    }
}

}
