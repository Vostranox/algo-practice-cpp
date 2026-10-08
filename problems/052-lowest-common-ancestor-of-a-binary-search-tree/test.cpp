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

static void run_many(TreeNode* root, const string& label, const vector<array<int, 3>>& queries) {
    unordered_map<int, TreeNode*> by_val;
    for (auto* n : tree_nodes(root)) {
        by_val[n->val] = n;
    }
    Solution sol;
    for (auto [p, q, want] : queries) {
        TreeNode* got = sol.lowestCommonAncestor(root, by_val.at(p), by_val.at(q));
        verify(got, by_val.at(want), [&] { return input_line("root", label, "p", p, "q", q); });
    }
}

struct Bst {
    vector<TreeNode*> nodes;
    vector<int> parent, depth;

    TreeNode* build(const vector<int>& vals, int lo, int hi, int par, int d) {
        if (lo > hi) return nullptr;
        int mid = (lo + hi) / 2;
        TreeNode* node = nodes[mid] = new TreeNode(vals[mid]);
        parent[mid] = par, depth[mid] = d;
        node->left = build(vals, lo, mid - 1, mid, d + 1);
        node->right = build(vals, mid + 1, hi, mid, d + 1);
        return node;
    }
};

TEST(examples) {
    run({20, 10, 30, 5, 15, 25, 35}, 5, 15, 10);
    run({20, 10, 30, 5, 15, 25, 35}, 10, 15, 10);
    run({20, 10, 30, 5, 15, 25, 35}, 35, 5, 20);
}

TEST(edge_cases) {
    run({2, 1}, 2, 1, 2);
    run({2, 1}, 1, 2, 2);
    run({1, null, 2}, 1, 2, 1);
    run({1, null, 2}, 2, 1, 1);
    run({20, 10, 30, 5, 15, 25, 35}, 15, 5, 10);
    run({20, 10, 30, 5, 15, 25, 35}, 35, 25, 30);
    run({20, 10, 30, 5, 15, 25, 35}, 20, 35, 20);
    run({20, 10, 30, 5, 15, 25, 35}, 15, 25, 20);
    run({0, -1000000000, 1000000000}, -1000000000, 1000000000, 0);
    run({50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45}, 25, 45, 30);
    run({50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45}, 10, 25, 20);
    run({50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45}, 35, 40, 40);
    run({50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45}, 45, 60, 50);
    run({-5, -8, 7, null, -6, 0, null, null, null, -2, 3}, -2, 3, 0);
}

TEST(deep) {
    const int K = 10000;
    TreeNode* root = new TreeNode(0, new TreeNode(-5), nullptr);
    TreeNode* spine = root;
    for (int i = 1; i < K; ++i) {
        spine = spine->right = new TreeNode(10 * i);
        spine->left = new TreeNode(10 * i - 5);
    }
    const int last = 10 * (K - 1);
    run_many(root, "right spine 0, 10, ..., 99990, each node 10*i with a left leaf 10*i - 5",
             {{last - 5, last - 15, last - 10}, {-5, last - 5, 0}, {10 * 5000 - 5, last, 10 * 5000},
              {last, last - 10, last - 10}, {last, last - 5, last}});

    const int N = 10000;
    TreeNode* top = new TreeNode(1);
    TreeNode* node = top;
    for (int i = 1; i < N; ++i) {
        int v = i % 2 ? N - i / 2 : 1 + i / 2;
        TreeNode* child = new TreeNode(v);
        (v > node->val ? node->right : node->left) = child;
        node = child;
    }
    run_many(top, "zigzag BST 1 -> 10000 -> 2 -> 9999 -> ... -> 5000 -> 5001",
             {{N / 2, N / 2 + 1, N / 2}, {N / 2 + 1, 1, 1}, {N - 1, N / 2 - 1, N - 1}, {N / 2 - 1, N / 2, N / 2 - 1}});
}

TEST(large) {
    Rng rng(52);
    const int N = 100000;
    vector<int> vals;
    unordered_set<int> seen;
    while (static_cast<int>(vals.size()) < N) {
        int v = rng(-1000000000, 1000000000);
        if (seen.insert(v).second) {
            vals.push_back(v);
        }
    }
    sort(vals.begin(), vals.end());
    Bst t{vector<TreeNode*>(N), vector<int>(N), vector<int>(N)};
    TreeNode* root = t.build(vals, 0, N - 1, -1, 0);
    auto lca = [&](int a, int b) {
        while (t.depth[a] > t.depth[b]) {
            a = t.parent[a];
        }
        while (t.depth[b] > t.depth[a]) {
            b = t.parent[b];
        }
        while (a != b) {
            a = t.parent[a], b = t.parent[b];
        }
        return a;
    };
    Solution sol;
    for (int done = 0; done < N;) {
        int a, b;
        if (done % 3 == 0) {
            b = rng(0, N - 1);
            if (t.depth[b] == 0) continue;
            a = b;
            for (int up = rng(1, t.depth[b]); up > 0; --up) {
                a = t.parent[a];
            }
        } else if (done % 3 == 1) {
            a = rng(0, N - 4);
            b = a + rng(1, 3);
        } else {
            a = rng(0, N - 1), b = rng(0, N - 1);
            if (a == b) continue;
        }
        if (rng.coin()) {
            swap(a, b);
        }
        TreeNode* got = sol.lowestCommonAncestor(root, t.nodes[a], t.nodes[b]);
        verify(got, t.nodes[lca(a, b)], [&] {
            return input_line("root", string("balanced BST with 10^5 distinct values"), "p", vals[a], "q", vals[b]);
        });
        ++done;
    }
}

}
