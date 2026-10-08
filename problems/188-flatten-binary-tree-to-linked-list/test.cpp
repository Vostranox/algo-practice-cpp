#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void preorder_of(TreeNode* n, vector<TreeNode*>& out) {
    if (!n) return;
    out.push_back(n);
    preorder_of(n->left, out);
    preorder_of(n->right, out);
}

static Tree as_list(const vector<TreeNode*>& nodes) {
    Tree out;
    for (TreeNode* n : nodes) {
        if (!out.empty()) {
            out.push_back(null);
        }
        out.push_back(n->val);
    }
    return out;
}

template <class Input>
static void verify(TreeNode* root, Tree want, Input input) {
    vector<TreeNode*> pre;
    preorder_of(root, pre);
    if (want.empty()) {
        want = as_list(pre);
    }
    Solution().flatten(root);
    vector<TreeNode*> got;
    unordered_set<TreeNode*> seen;
    for (TreeNode* n = root; n; n = n->right) {
        if (!seen.insert(n).second) {
            fail(input() + "problem:  the right pointers run in a cycle (back to the node with val " +
                 to_string(n->val) + ")");
        }
        if (n->left) {
            fail(input() + "problem:  list entry " + to_string(got.size()) + " (val " + to_string(n->val) +
                 ") still has a left child; every left pointer must be nullptr");
        }
        got.push_back(n);
    }
    if (as_list(got) != want) {
        fail(input() + "expected: " + clip(repr(want)) + "\ngot:      " + clip(repr(as_list(got))));
    }
    for (size_t i = 0; i < pre.size(); ++i) {
        if (got[i] != pre[i]) {
            fail(input() + "problem:  list entry " + to_string(i) + " (val " + to_string(got[i]->val) +
                 ") is not the original node: rearrange the tree's own nodes, don't create new ones");
        }
    }
}

static void run(const Tree& vals, const Tree& want) {
    verify(build_tree(vals), want, [&] { return input_line("root", vals); });
}

static void run_big(TreeNode* root, const string& label) {
    verify(root, {}, [&] { return input_line("root", label); });
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

static TreeNode* chain(int n, const string& sides) {
    TreeNode* root = new TreeNode(0);
    TreeNode* cur = root;
    for (int i = 1; i < n; ++i) {
        TreeNode* child = new TreeNode(i % 201 - 100);
        (sides[i % sides.size()] == 'L' ? cur->left : cur->right) = child;
        cur = child;
    }
    return root;
}

TEST(examples) {
    run({5, 3, 8, 1, 4, null, 9}, {5, null, 3, null, 1, null, 4, null, 8, null, 9});
    run({1, null, 2, 3}, {1, null, 2, null, 3});
    run({}, {});
}

TEST(edge_cases) {
    run({0}, {0});
    run({1, 2}, {1, null, 2});
    run({1, null, 2}, {1, null, 2});
    run({1, 2, 3}, {1, null, 2, null, 3});
    run({1, 2, null, 3, null, 4}, {1, null, 2, null, 3, null, 4});
    run({1, 2, 5, 3, 4, null, 6}, {1, null, 2, null, 3, null, 4, null, 5, null, 6});
    run({1, 2, null, null, 3, 4}, {1, null, 2, null, 3, null, 4});
    run({-100, 100, -100, 100}, {-100, null, 100, null, 100, null, -100});
    run({7, 7, 7, 7, 7}, {7, null, 7, null, 7, null, 7, null, 7});
    run({10, 20, 30, null, 21, null, null, 22, 23}, {10, null, 20, null, 21, null, 22, null, 23, null, 30});
}

TEST(large) {
    run_big(build_tree(Tree(2000, 1)), "complete tree with 2000 nodes, all values 1");
    Tree full(2000);
    for (int i = 0; i < 2000; ++i) {
        full[i] = i % 201 - 100;
    }
    run_big(build_tree(full), "complete tree with 2000 nodes, values -100, -99, ... in level order");
    run_big(chain(2000, "L"), "chain of 2000 left children");
    run_big(chain(2000, "R"), "chain of 2000 right children (already flat)");
    run_big(chain(2000, "LR"), "zigzag chain of 2000 nodes");
    run_big(chain(2000, "LLR"), "chain of 2000 nodes going left, left, right, ...");
    Rng rng(188);
    for (int i = 0; i < 3; ++i) {
        run_big(random_tree(rng, 2000, -100, 100), "random tree with 2000 nodes");
    }
}

TEST(random) {
    Rng rng(1880);
    for (int i = 0; i < 500; ++i) {
        TreeNode* t = random_tree(rng, rng(0, 30), -100, 100);
        Tree vals = tree_to_vec(t);
        verify(t, {}, [&] { return input_line("root", vals); });
    }
}

}
