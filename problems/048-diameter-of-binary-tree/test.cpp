#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int want) {
    check(Solution().diameterOfBinaryTree(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, int want, const string& label) {
    check(Solution().diameterOfBinaryTree(root), want, "root", label);
}

static TreeNode* spine(int k, const string& sides, bool leaves) {
    TreeNode* root = new TreeNode(0);
    TreeNode* cur = root;
    for (int i = 1; i < k; ++i) {
        bool left = sides[i % sides.size()] == 'L';
        TreeNode* next = new TreeNode(i % 100);
        (left ? cur->left : cur->right) = next;
        if (leaves) {
            (left ? cur->right : cur->left) = new TreeNode(-1);
        }
        cur = next;
    }
    return root;
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

static int brute_diameter(TreeNode* root) {
    vector<TreeNode*> nodes = tree_nodes(root);
    unordered_map<TreeNode*, vector<TreeNode*>> adj;
    for (auto* n : nodes) {
        for (auto* c : {n->left, n->right}) {
            if (c) {
                adj[n].push_back(c);
                adj[c].push_back(n);
            }
        }
    }
    int best = 0;
    for (auto* s : nodes) {
        unordered_map<TreeNode*, int> dist{{s, 0}};
        deque<TreeNode*> q{s};
        while (!q.empty()) {
            TreeNode* u = q.front();
            q.pop_front();
            best = max(best, dist[u]);
            for (auto* v : adj[u]) {
                if (!dist.count(v)) {
                    dist[v] = dist[u] + 1;
                    q.push_back(v);
                }
            }
        }
    }
    return best;
}

TEST(examples) {
    run({6, 2, 9, 1, 4, null, null, null, null, 3}, 4);
    run({1, 2, null, 3, 4, 5, null, null, 6}, 4);
    run({8}, 0);
}

TEST(edge_cases) {
    run({1, 2}, 1);
    run({1, null, 2}, 1);
    run({1, 2, 3}, 2);
    run({1, 2, null, 3, null, 4, null, 5}, 4);
    run({0, 0, 0, 0, 0, 0, 0}, 4);
    run({-1, -2, -3, -4, null, null, -5, -6, null, null, -7}, 6);
    run({1, 2, 3, 4, 5, null, null, 6, null, null, 7, 8, null, null, 9}, 6);
}

TEST(large) {
    run_big(spine(5000, "L", true), 5000, "left spine of 5000 nodes, each with a right leaf");
    run_big(spine(5000, "R", true), 5000, "right spine of 5000 nodes, each with a left leaf");
    run_big(spine(5000, "LR", true), 5000, "zigzag spine of 5000 nodes with leaves");
    run_big(spine(10000, "L", false), 9999, "chain of 10^4 left children");
    for (char down : {'L', 'R'}) {
        TreeNode* root = spine(6000, string(1, down), false);
        TreeNode* node = root;
        for (int i = 0; i < 2000; ++i) {
            node = down == 'L' ? node->left : node->right;
        }
        for (int i = 0; i < 4000; ++i) {
            TreeNode* b = new TreeNode(i % 100);
            (down == 'L' ? node->right : node->left) = b;
            node = b;
        }
        run_big(root, 7999, string(down == 'L' ? "left" : "right") +
                                " spine of 6000 with a 4000-node branch on the other side at depth 2000");
    }
    Tree full(10000);
    for (int i = 0; i < 10000; ++i) {
        full[i] = i % 100 - 50;
    }
    run_big(build_tree(full), 13 + 12, "complete tree with 10^4 nodes");
}

TEST(random) {
    Rng rng(48);
    for (int i = 0; i < 300; ++i) {
        TreeNode* t = random_tree(rng, rng(1, 40), -100, 100);
        run(tree_to_vec(t), brute_diameter(t));
    }
}

}
