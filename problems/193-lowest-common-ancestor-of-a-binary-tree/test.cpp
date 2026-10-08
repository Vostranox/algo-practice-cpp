#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

template <class Input>
static void verify(TreeNode* got, TreeNode* want, Input input) {
    if (got == want) return;
    string msg = input() + "expected: node " + to_string(want->val) +
                 "\ngot:      " + (got ? "node " + to_string(got->val) : string("nullptr"));
    if (got && got->val == want->val) {
        msg += "\nproblem:  the returned node has the right value but is not the node from the input tree";
    }
    fail(msg);
}

static void run(const Tree& vals, int p, int q, int want) {
    TreeNode* root = build_tree(vals);
    TreeNode* got = Solution().lowestCommonAncestor(root, find_node(root, p), find_node(root, q));
    verify(got, find_node(root, want), [&] { return input_line("root", vals, "p", p, "q", q); });
}

struct Parents {
    vector<TreeNode*> nodes;
    vector<int> parent, depth;
    explicit Parents(TreeNode* root) : nodes{root}, parent{-1}, depth{0} {
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (TreeNode* c : {nodes[i]->left, nodes[i]->right}) {
                if (c) {
                    nodes.push_back(c);
                    parent.push_back(static_cast<int>(i));
                    depth.push_back(depth[i] + 1);
                }
            }
        }
    }
    int lca(int a, int b) const {
        while (depth[a] > depth[b]) {
            a = parent[a];
        }
        while (depth[b] > depth[a]) {
            b = parent[b];
        }
        while (a != b) {
            a = parent[a], b = parent[b];
        }
        return a;
    }
    template <class Input>
    void query(TreeNode* root, int a, int b, Input input) const {
        TreeNode* got = Solution().lowestCommonAncestor(root, nodes[a], nodes[b]);
        verify(got, nodes[lca(a, b)], input);
    }
};

static void run_many(TreeNode* root, const string& label, Rng& rng, vector<pair<int, int>> pairs, int random) {
    Parents t(root);
    int n = static_cast<int>(t.nodes.size());
    for (auto& [a, b] : pairs) {
        if (a < 0) {
            a += n;
        }
        if (b < 0) {
            b += n;
        }
    }
    for (int i = 0; i < random; ++i) {
        int a = rng(0, n - 1), b = rng(0, n - 1);
        if (a != b) {
            pairs.push_back({a, b});
        }
    }
    for (auto [a, b] : pairs) {
        t.query(root, a, b, [&] { return input_line("root", label, "p", t.nodes[a]->val, "q", t.nodes[b]->val); });
    }
}

static TreeNode* random_tree(Rng& rng, int n, int lo, int step) {
    vector<int> vals(n);
    for (int i = 0; i < n; ++i) {
        vals[i] = lo + i * step + rng(0, step - 1);
    }
    rng.shuffle(vals);
    TreeNode* root = new TreeNode(vals[0]);
    vector<TreeNode**> slots{&root->left, &root->right};
    for (int i = 1; i < n; ++i) {
        swap(slots[rng.next() % slots.size()], slots.back());
        TreeNode** s = slots.back();
        slots.pop_back();
        *s = new TreeNode(vals[i]);
        slots.push_back(&(*s)->left);
        slots.push_back(&(*s)->right);
    }
    return root;
}

static TreeNode* chain(int n, const string& sides, bool twigs) {
    TreeNode* root = new TreeNode(1);
    TreeNode* cur = root;
    for (int i = 1; i < n; ++i) {
        TreeNode* child = new TreeNode(i + 1);
        bool left = sides[i % sides.size()] == 'L';
        (left ? cur->left : cur->right) = child;
        if (twigs) {
            (left ? cur->right : cur->left) = new TreeNode(-cur->val);
        }
        cur = child;
    }
    return root;
}

TEST(examples) {
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 9, 1, 4);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 2, 8, 2);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 8, 5, 10);
}

TEST(edge_cases) {
    run({1, 2}, 1, 2, 1);
    run({1, 2}, 2, 1, 1);
    run({1, null, 2}, 2, 1, 1);
    run({1, 2, 3}, 2, 3, 1);
    run({1, 2, 3}, 3, 2, 1);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 8, 1, 2);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 9, 2, 4);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 5, 7, 7);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 10, 5, 10);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 1, 4, 4);
    run({10, 4, 7, 9, 2, null, 5, null, null, 8, 1}, 1, 9, 4);
    run({-5, 1000000000, -1000000000}, 1000000000, -1000000000, -5);
    run({0, -1, null, -2, -3, -4, null, null, -5}, -4, -5, -1);
    run({0, -1, null, -2, -3, -4, null, null, -5}, -5, -3, -3);
    run({8, 9, 6, null, null, 7, 5}, 7, 5, 6);
    run({8, 9, 6, null, null, 7, 5}, 9, 5, 8);
}

TEST(deep) {
    Rng rng(193);
    const int N = 100000;
    run_many(chain(N, "L", false), "chain of 10^5 left children", rng, {{-1, -2}, {0, -1}, {-1, N / 2}}, 1);
    run_many(chain(N, "R", false), "chain of 10^5 right children", rng, {{-2, -1}, {N / 2, -1}}, 1);
    run_many(chain(N / 2, "LR", true), "zigzag spine of 5 * 10^4 nodes, each with a leaf", rng,
             {{-1, -2}, {-1, -3}, {-2, -3}, {-1, 1}, {1, 2}}, 0);
}

TEST(large) {
    Rng rng(1931);
    const int N = 100000;
    Tree full(N);
    for (int i = 0; i < N; ++i) {
        full[i] = 1000000000 - 2 * i;
    }
    run_many(build_tree(full), "complete tree with 10^5 nodes", rng, {{-1, -2}, {-1, N / 2 - 1}, {1, 2}}, 1);
    for (int i = 0; i < 2; ++i) {
        run_many(random_tree(rng, N, -1000000000, 20000), "random tree with 10^5 nodes", rng, {{-1, -2}}, 2);
    }
}

TEST(random) {
    Rng rng(1930);
    for (int i = 0; i < 300; ++i) {
        int n = rng(2, 25);
        TreeNode* root = random_tree(rng, n, -25, 2);
        Tree vals = tree_to_vec(root);
        Parents t(root);
        int a = rng(0, n - 1), b = rng(0, n - 2);
        if (b >= a) {
            ++b;
        }
        t.query(root, a, b, [&] { return input_line("root", vals, "p", t.nodes[a]->val, "q", t.nodes[b]->val); });
    }
}

}
