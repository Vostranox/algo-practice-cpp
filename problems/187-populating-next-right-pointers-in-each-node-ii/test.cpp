#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static NextNode* build(const Tree& vals) {
    if (vals.empty() || !vals[0]) return nullptr;
    NextNode* root = new NextNode(*vals[0]);
    deque<NextNode*> q{root};
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        NextNode* n = q.front();
        q.pop_front();
        if (i < vals.size() && vals[i]) {
            q.push_back(n->left = new NextNode(*vals[i]));
        }
        ++i;
        if (i < vals.size() && vals[i]) {
            q.push_back(n->right = new NextNode(*vals[i]));
        }
        ++i;
    }
    return root;
}

static NextNode* copy_of(const TreeNode* n) {
    return n ? new NextNode(n->val, copy_of(n->left), copy_of(n->right), nullptr) : nullptr;
}

static vector<vector<NextNode*>> levels_of(NextNode* root) {
    vector<vector<NextNode*>> levels;
    vector<NextNode*> cur;
    if (root) {
        cur.push_back(root);
    }
    while (!cur.empty()) {
        levels.push_back(cur);
        vector<NextNode*> below;
        for (NextNode* n : cur) {
            if (n->left) {
                below.push_back(n->left);
            }
            if (n->right) {
                below.push_back(n->right);
            }
        }
        cur = move(below);
    }
    return levels;
}

static vector<string> follow_next(const vector<vector<NextNode*>>& levels) {
    vector<string> out;
    for (auto& level : levels) {
        string s;
        NextNode* p = level[0];
        for (size_t steps = 0; p && steps <= level.size(); p = p->next, ++steps) {
            s += to_string(p->val) + ", ";
        }
        out.push_back(s + (p ? "..., #" : "#"));
    }
    return out;
}

static vector<string> by_levels(const vector<vector<NextNode*>>& levels) {
    vector<string> out;
    for (auto& level : levels) {
        string s;
        for (NextNode* n : level) {
            s += to_string(n->val) + ", ";
        }
        out.push_back(s + "#");
    }
    return out;
}

static string joined(const vector<string>& parts) {
    string out;
    for (auto& p : parts) {
        out += (out.empty() ? "" : ", ") + p;
    }
    return "[" + out + "]";
}

template <class Input>
static void verify(NextNode* root, string want, Input input) {
    auto levels = levels_of(root);
    vector<string> want_parts = by_levels(levels);
    if (want.empty()) {
        want = joined(want_parts);
    }
    struct Saved {
        NextNode *node, *left, *right;
        int val;
    };
    vector<Saved> saved;
    for (auto& level : levels) {
        for (NextNode* n : level) {
            saved.push_back({n, n->left, n->right, n->val});
        }
    }

    NextNode* got = Solution().connect(root);

    for (auto& s : saved) {
        if (s.node->left != s.left || s.node->right != s.right || s.node->val != s.val) {
            fail(input() + "problem:  the node with val " + to_string(s.val) +
                 " was changed (only next pointers may be set)");
        }
    }
    vector<string> got_parts = follow_next(levels);
    if (joined(got_parts) != want) {
        string msg = input() + "expected: " + clip(want) + "\ngot:      " + clip(joined(got_parts));
        for (size_t d = 0; d < levels.size(); ++d) {
            if (got_parts[d] != want_parts[d]) {
                msg += "\nfirst wrong level: " + to_string(d) + " (the root's level is 0)\n  expected: " +
                       clip(want_parts[d], 200) + "\n  got:      " + clip(got_parts[d], 200);
                break;
            }
        }
        fail(msg);
    }
    for (size_t d = 0; d < levels.size(); ++d) {
        for (size_t i = 0; i < levels[d].size(); ++i) {
            NextNode* expect = i + 1 < levels[d].size() ? levels[d][i + 1] : nullptr;
            if (levels[d][i]->next != expect) {
                fail(input() + "problem:  node " + to_string(i) + " (from the left, val " +
                     to_string(levels[d][i]->val) + ") of level " + to_string(d) +
                     ": next points to the wrong node (one with the right value, but not the node that is "
                     "really next on its level)");
            }
        }
    }
    if (got != root) {
        fail(input() + "problem:  connect must return the root it was given");
    }
}

static void run(const Tree& vals, const string& want) {
    verify(build(vals), want, [&] { return input_line("root", vals); });
}

static void run_big(NextNode* root, const string& label) {
    verify(root, "", [&] { return input_line("root", label); });
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

static NextNode* chain(int n, const string& sides) {
    NextNode* root = new NextNode(0);
    NextNode* cur = root;
    for (int i = 1; i < n; ++i) {
        NextNode* child = new NextNode(i % 201 - 100);
        (sides[i % sides.size()] == 'L' ? cur->left : cur->right) = child;
        cur = child;
    }
    return root;
}

TEST(examples) {
    run({6, 3, 9, null, 4, 8, null, 1, null, null, 5}, "[6, #, 3, 9, #, 4, 8, #, 1, 5, #]");
    run({10, 20, 30, 40, 50, null, 60, 70, null, null, null, null, 80}, "[10, #, 20, 30, #, 40, 50, 60, #, 70, 80, #]");
    run({}, "[]");
}

TEST(edge_cases) {
    run({0}, "[0, #]");
    run({1, 2}, "[1, #, 2, #]");
    run({1, null, 2}, "[1, #, 2, #]");
    run({1, 2, 3}, "[1, #, 2, 3, #]");
    run({1, 2, 3, 4, 5, 6, 7}, "[1, #, 2, 3, #, 4, 5, 6, 7, #]");
    run({1, 2, 3, 4, null, null, 5}, "[1, #, 2, 3, #, 4, 5, #]");
    run({1, 2, 3, null, 4, 5}, "[1, #, 2, 3, #, 4, 5, #]");
    run({7, 7, 7, 7, null, null, 7}, "[7, #, 7, 7, #, 7, 7, #]");
    run({1, 2, 3, 4, 5, null, null, 6, null, null, 7}, "[1, #, 2, 3, #, 4, 5, #, 6, 7, #]");
    run({2, 1, 3, 0, 7, 9, 1, 2, null, 1, 0, null, null, 8, 8, null, null, null, null, 7},
        "[2, #, 1, 3, #, 0, 7, 9, 1, #, 2, 1, 0, 8, 8, #, 7, #]");
    run({-100, null, 100, null, -5, 5}, "[-100, #, 100, #, -5, #, 5, #]");
}

TEST(large) {
    Tree full(6000);
    for (int i = 0; i < 6000; ++i) {
        full[i] = i % 201 - 100;
    }
    run_big(build(full), "complete tree with 6000 nodes");
    run_big(chain(6000, "L"), "chain of 6000 left children");
    run_big(chain(6000, "R"), "chain of 6000 right children");
    run_big(chain(6000, "LR"), "zigzag chain of 6000 nodes");

    Tree perfect(2047, 1);
    NextNode* root = build(perfect);
    NextNode *a = root, *b = root;
    while (a->left) {
        a = a->left, b = b->right;
    }
    for (int i = 0; i < 1976; ++i) {
        a = (i % 3 ? a->left : a->right) = new NextNode(-i % 101);
        b = (i % 2 ? b->left : b->right) = new NextNode(i % 101);
    }
    run_big(root, "perfect tree of 2047 nodes with two 1976-node chains below its outermost leaves");

    Rng rng(187);
    for (int i = 0; i < 3; ++i) {
        run_big(copy_of(random_tree(rng, 6000, -100, 100)), "random tree with 6000 nodes");
    }
}

TEST(random) {
    Rng rng(1870);
    for (int i = 0; i < 500; ++i) {
        TreeNode* t = random_tree(rng, rng(0, 40), -100, 100);
        Tree vals = tree_to_vec(t);
        verify(copy_of(t), "", [&] { return input_line("root", vals); });
    }
}

}
