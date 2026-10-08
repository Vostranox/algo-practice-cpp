#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const Tree& root, int want) {
    check(Solution().countNodes(build_tree(root)), want, "root", root);
}

static Tree complete(int n, Rng& rng) {
    Tree vals(n);
    for (auto& v : vals) {
        v = rng(0, 50000);
    }
    return vals;
}

struct Heap {
    vector<TreeNode*> node;
    int m = 0;
    explicit Heap(int n) : node(n) {
        for (int i = 0; i < n; ++i) {
            node[i] = new TreeNode(i);
        }
    }
    TreeNode*& slot(int i) { return i % 2 ? node[(i - 1) / 2]->left : node[(i - 1) / 2]->right; }
    void resize(int want) {
        for (; m < want; ++m) {
            if (m > 0) {
                slot(m) = node[m];
            }
        }
        for (; m > want; --m) {
            if (m > 1) {
                slot(m - 1) = nullptr;
            }
        }
    }
    TreeNode* root() { return m ? node[0] : nullptr; }
};

TEST(examples) {
    run({9, 4, 7, 1, 3, 8, 2, 5}, 8);
    run({6, 6, 6}, 3);
    run({}, 0);
}

TEST(edge_cases) {
    run({0}, 1);
    run({1, 2}, 2);
    run({1, 2, 3}, 3);
    run({1, 2, 3, 4}, 4);
    run({1, 2, 3, 4, 5}, 5);
    run({1, 2, 3, 4, 5, 6, 7}, 7);
    run({1, 2, 3, 4, 5, 6, 7, 8}, 8);
    run({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, 14);
    run({50000, 0, 50000, 0, 50000, 0, 50000, 0, 50000, 0, 50000, 0, 50000, 0, 50000}, 15);
    run({5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 16);
}

TEST(large) {
    Rng rng(192);
    for (int n : {50000, 49999, 32767, 32768, 32766, 49152, 49153, 40000}) {
        check(Solution().countNodes(build_tree(complete(n, rng))), n, "root",
              "complete tree with " + to_string(n) + " nodes");
    }
}

TEST(many_calls) {
    const int N = 50000;
    Rng rng(1922);
    Heap h(N);
    Solution sol;
    vector<int> centers{N, 32767, 49152};
    for (int i = 0; i < 100000; ++i) {
        if (i % 2000 == 0) {
            h.resize(i / 2000 < 3 ? centers[i / 2000] : rng(40000, N));
        } else {
            h.resize(min(N, max(32000, h.m + rng(-20, 20))));
        }
        int got = sol.countNodes(h.root());
        if (got != h.m) {
            check(got, h.m, "root", "complete tree with " + to_string(h.m) + " nodes (call #" + to_string(i) + ")");
        }
    }
}

TEST(random) {
    Rng rng(1920);
    for (int n = 0; n <= 300; ++n) {
        run(complete(n, rng), n);
    }
    for (int i = 0; i < 100; ++i) {
        int n = rng(0, 3000);
        Tree vals = complete(n, rng);
        check(Solution().countNodes(build_tree(vals)), n, "root", vals);
    }
}

}
