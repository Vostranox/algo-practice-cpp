#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static bool inorder(TreeNode* n, vector<int>& out, unordered_set<TreeNode*>& seen) {
    if (!n) return true;
    if (!seen.insert(n).second) return false;
    if (!inorder(n->left, out, seen)) return false;
    out.push_back(n->val);
    return inorder(n->right, out, seen);
}

static int height(TreeNode* n, TreeNode*& bad) {
    if (!n) return 0;
    int l = height(n->left, bad), r = height(n->right, bad);
    if (abs(l - r) > 1 && !bad) {
        bad = n;
    }
    return 1 + max(l, r);
}

template <class Input>
static void verify(TreeNode* got, const vector<int>& nums, Input input) {
    vector<int> in;
    unordered_set<TreeNode*> seen;
    if (!inorder(got, in, seen)) {
        fail(input() + "problem:  the returned tree contains a cycle or a node used twice");
    }
    if (in != nums) {
        fail(input() + "problem:  the tree's inorder sequence (its values in BST order) must be exactly nums\n"
                       "inorder:  " + clip(repr(in)) + "\ngot:      " + clip(repr(got)));
    }
    TreeNode* bad = nullptr;
    height(got, bad);
    if (bad) {
        TreeNode* unused = nullptr;
        fail(input() + "problem:  not height-balanced at the node with val " + to_string(bad->val) +
             ": its left subtree has height " + to_string(height(bad->left, unused)) + ", its right subtree " +
             to_string(height(bad->right, unused)) + "\ngot:      " + clip(repr(got)));
    }
}

static void run(const vector<int>& nums) {
    vector<int> arg = nums;
    verify(Solution().sortedArrayToBST(arg), nums, [&] { return input_line("nums", nums); });
}

static void run_big(const vector<int>& nums, const string& label) {
    vector<int> arg = nums;
    verify(Solution().sortedArrayToBST(arg), nums, [&] { return input_line("nums", label); });
}

static vector<int> random_sorted(Rng& rng, int n) {
    vector<int> pool(20001);
    iota(pool.begin(), pool.end(), -10000);
    rng.shuffle(pool);
    pool.resize(n);
    return sorted(pool);
}

TEST(examples) {
    run({-6, -2, 0, 5, 9});
    run({1, 3});
    run({7});
}

TEST(edge_cases) {
    run({-10000});
    run({10000});
    run({-10000, 10000});
    run({1, 2, 3});
    run({1, 2, 3, 4});
    run({1, 2, 3, 4, 5, 6});
    run({1, 2, 3, 4, 5, 6, 7});
    run({1, 2, 3, 4, 5, 6, 7, 8});
    run({-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6});
    run({0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160});
}

TEST(large) {
    Rng rng(202);
    run_big(random_sorted(rng, 10000), "10^4 random distinct values from [-10^4, 10^4]");
    for (int n : {10000, 8191, 8192, 8193, 6143, 6144, 9999}) {
        vector<int> nums(n);
        iota(nums.begin(), nums.end(), -n / 2);
        run_big(nums, to_string(n) + " consecutive values from " + to_string(-n / 2));
    }
}

TEST(random) {
    Rng rng(2020);
    for (int n = 1; n <= 70; ++n) {
        run(random_sorted(rng, n));
    }
    for (int i = 0; i < 100; ++i) {
        run(random_sorted(rng, rng(1, 1000)));
    }
}

}
