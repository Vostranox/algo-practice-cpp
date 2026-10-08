#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

struct Case {
    Tree vals;
    string label;
};

static void check_case(const Tree& got, const Tree& want, const Case& c, const string& data) {
    if (c.label.empty()) {
        check(got, want, "root", c.vals, "data", data);
    } else {
        check(got, want, "root", c.label, "data", data);
    }
}

static void ensure_case(bool ok, const string& problem, const Case& c, const string& data) {
    if (c.label.empty()) {
        ensure(ok, problem, "root", c.vals, "data", data);
    } else {
        ensure(ok, problem, "root", c.label, "data", data);
    }
}

static void roundtrip(const vector<Case>& cases) {
    vector<string> data;
    unordered_set<TreeNode*> old;
    for (auto& c : cases) {
        TreeNode* t = build_tree(c.vals);
        for (auto* n : tree_nodes(t)) {
            old.insert(n);
        }
        Codec ser;
        data.push_back(ser.serialize(t));
    }
    for (auto* n : old) {
        n->val = 12345;
        n->left = n->right = nullptr;
    }
    for (size_t i = cases.size(); i-- > 0;) {
        Codec deser;
        TreeNode* got = deser.deserialize(data[i]);
        Tree got_vals = tree_to_vec(got);
        bool reused = false;
        for (auto* n : tree_nodes(got)) {
            reused = reused || old.count(n);
        }
        ensure_case(!reused, "deserialize returned nodes of the original tree; it must build new ones", cases[i], data[i]);
        check_case(got_vals, tree_to_vec(build_tree(cases[i].vals)), cases[i], data[i]);
    }
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
    TreeNode* root = new TreeNode(-1000);
    TreeNode* cur = root;
    for (int i = 1; i < n; ++i) {
        TreeNode* child = new TreeNode(i % 2001 - 1000);
        (sides[i % sides.size()] == 'L' ? cur->left : cur->right) = child;
        cur = child;
    }
    return root;
}

TEST(examples) {
    roundtrip({{{7, -3, 12, null, 5, 100}, ""}});
    roundtrip({{{}, ""}});
}

TEST(edge_cases) {
    roundtrip({
        {{}, ""},
        {{0}, ""},
        {{-1000}, ""},
        {{1000, -1000, 999}, ""},
        {{1, 2}, ""},
        {{1, null, 2}, ""},
        {{-12, -345, 678, null, null, -9}, ""},
        {{5, 5, 5, null, 5, 5}, ""},
        {{0, 0, 0, 0, null, null, 0}, ""},
        {{1, 2, null, 3, null, 4, null, 5}, ""},
        {{1, null, 2, null, 3, null, 4, null, 5}, ""},
        {{1, 2, null, null, 3, 4, null, null, 5}, ""},
        {{10, 1, 100, null, 11, 101}, ""},
    });
}

TEST(large) {
    Tree full(10000);
    for (int i = 0; i < 10000; ++i) {
        full[i] = i % 2001 - 1000;
    }
    Rng rng(60);
    roundtrip({
        {full, "complete tree of 10^4 nodes, values -1000..1000"},
        {tree_to_vec(chain(10000, "L")), "chain of 10^4 left children"},
        {tree_to_vec(chain(10000, "R")), "chain of 10^4 right children"},
        {tree_to_vec(chain(10000, "LRR")), "chain of 10^4 nodes going left, right, right, ..."},
        {tree_to_vec(random_tree(rng, 10000, -1000, 1000)), "random tree of 10^4 nodes"},
    });
}

TEST(random) {
    Rng rng(600);
    vector<Case> cases;
    for (int i = 0; i < 300; ++i) {
        cases.push_back({tree_to_vec(random_tree(rng, rng(0, 30), -1000, 1000)), ""});
    }
    roundtrip(cases);
}

}
