#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int want) {
    check(Solution().maxPathSum(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, int want, const string& label) {
    check(Solution().maxPathSum(root), want, "root", label);
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

static int64_t brute(TreeNode* root) {
    unordered_map<TreeNode*, TreeNode*> parent;
    vector<TreeNode*> nodes = tree_nodes(root);
    for (auto* n : nodes) {
        for (auto* c : {n->left, n->right}) {
            if (c) {
                parent[c] = n;
            }
        }
    }
    auto up_path = [&](TreeNode* n) {
        vector<TreeNode*> out{n};
        while (parent.count(n)) {
            out.push_back(n = parent[n]);
        }
        return out;
    };
    int64_t best = INT64_MIN;
    for (auto* u : nodes) {
        for (auto* v : nodes) {
            vector<TreeNode*> pu = up_path(u), pv = up_path(v);
            unordered_set<TreeNode*> on_pu(pu.begin(), pu.end());
            int64_t sum = 0;
            TreeNode* lca = nullptr;
            for (auto* x : pv) {
                if (on_pu.count(x)) {
                    lca = x;
                    break;
                }
                sum += x->val;
            }
            for (auto* x : pu) {
                sum += x->val;
                if (x == lca) break;
            }
            best = max(best, sum);
        }
    }
    return best;
}

TEST(examples) {
    run({1, -2, 3}, 4);
    run({-5, 4, 8, null, null, 6, -1}, 14);
    run({-4, -2, -9}, -2);
}

TEST(edge_cases) {
    run({7}, 7);
    run({-1000}, -1000);
    run({-1, 10, 10}, 19);
    run({0, -1, -1}, 0);
    run({-3, -2, -1, -5}, -1);
    run({1, null, -5, null, 4, null, 6, null, -2}, 10);
    run({2, -1, -2}, 2);
    run({1, 2, 3, 4, 5, 6, 7}, 18);
    run({-10, 5, -20, 3, 4}, 12);
    run({1000, 1000, 1000, 1000, 1000, 1000, 1000}, 5000);
}

TEST(large) {
    const int n = 30000;
    run_big(build_tree(Tree(n, 1000)), 29 * 1000, "complete tree of 3*10^4 nodes, all 1000");
    Tree neg(n, -1000);
    neg[12345] = -1;
    run_big(build_tree(neg), -1, "complete tree of 3*10^4 nodes, all -1000 except one -1");

    TreeNode* top = new TreeNode(1000);
    TreeNode* cur = top;
    for (int i = 1; i < 10000; ++i) {
        cur = cur->right = new TreeNode(1000);
    }
    cur->left = build_tree(Tree(20000, 1000));
    run_big(top, (10000 + 15) * 1000, "chain of 10^4 nodes then a complete tree of 2*10^4 nodes, all 1000");

    top = new TreeNode(1000);
    cur = top;
    for (int i = 1; i < 10000; ++i) {
        cur = cur->left = new TreeNode(i == 5000 ? -1000 : 1000);
    }
    run_big(top, 9999 * 1000 - 1000, "chain of 10^4 values 1000 with one -1000 in the middle");
}

TEST(random) {
    Rng rng(59);
    for (int i = 0; i < 400; ++i) {
        TreeNode* t = random_tree(rng, rng(1, 12), -10, i % 3 ? 10 : -1);
        run(tree_to_vec(t), static_cast<int>(brute(t)));
    }
}

}
