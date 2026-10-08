#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int want) {
    check(Solution().sumNumbers(build_tree(root)), want, "root", root);
}

static void run_big(TreeNode* root, int want, const string& label) {
    check(Solution().sumNumbers(root), want, "root", label);
}

static void spell(TreeNode* n, string& digits, int64_t& total) {
    if (!n) return;
    digits += static_cast<char>('0' + n->val);
    if (!n->left && !n->right) {
        total += stoll(digits);
    }
    spell(n->left, digits, total);
    spell(n->right, digits, total);
    digits.pop_back();
}

static int64_t brute(TreeNode* root) {
    string digits;
    int64_t total = 0;
    spell(root, digits, total);
    return total;
}

static int height(TreeNode* n) { return n ? 1 + max(height(n->left), height(n->right)) : 0; }

static TreeNode* random_tree(Rng& rng, int n) {
    TreeNode* root = new TreeNode(rng(0, 9));
    vector<pair<TreeNode**, int>> slots{{&root->left, 2}, {&root->right, 2}};
    for (int i = 1; i < n; ++i) {
        swap(slots[rng.next() % slots.size()], slots.back());
        auto [s, depth] = slots.back();
        slots.pop_back();
        *s = new TreeNode(rng(0, 9));
        if (depth < 10) {
            slots.push_back({&(*s)->left, depth + 1});
            slots.push_back({&(*s)->right, depth + 1});
        }
    }
    return root;
}

static void make_fit(TreeNode* root) {
    vector<TreeNode*> level{root};
    while (brute(root) > INT_MAX) {
        vector<TreeNode*> below;
        for (TreeNode* n : level) {
            n->val = 0;
            if (n->left) {
                below.push_back(n->left);
            }
            if (n->right) {
                below.push_back(n->right);
            }
        }
        level = move(below);
    }
}

TEST(examples) {
    run({2, 7, 5, null, 3}, 298);
    run({0, 1, 6}, 7);
    run({1, 2, null, 3}, 123);
}

TEST(edge_cases) {
    run({0}, 0);
    run({9}, 9);
    run({1, 2}, 12);
    run({1, null, 2}, 12);
    run({1, 2, 3}, 25);
    run({9, 9, 9}, 198);
    run({0, 0, 0}, 0);
    run({0, 0, null, 0, null, 7}, 7);
    run({1, 0, 9, 4, null, null, null, 5}, 1064);
    run({5, 3, 0, null, 0, 0, 1}, 1531);
    run({2, 1, null, 4, null, 7, null, 4, null, 8, null, 3, null, 6, null, 4, null, 7}, 2147483647);
    run({1, 9, null, 9, null, 9, null, 9, null, 9, null, 9, null, 9, null, 9, null, 9}, 1999999999);
}

TEST(large) {
    Tree full(1000, 9);
    for (int i = 0; i < 15; ++i) {
        full[i] = 0;
    }
    run_big(build_tree(full), 489 * 999999 + 11 * 99999,
            "complete tree with 1000 nodes: 0 on the top 4 levels, 9 below");

    Rng rng(190);
    for (int i = 0; i < 4; ++i) {
        TreeNode* r = random_tree(rng, 1000);
        make_fit(r);
        if (height(r) > 10) {
            fail("test bug: tree too deep");
        }
        run_big(r, static_cast<int>(brute(r)), "random tree with 1000 nodes and depth <= 10");
    }
}

TEST(random) {
    Rng rng(1900);
    for (int i = 0; i < 500; ++i) {
        TreeNode* t = random_tree(rng, rng(1, i % 5 ? 15 : 200));
        make_fit(t);
        run(tree_to_vec(t), static_cast<int>(brute(t)));
    }
}

}
