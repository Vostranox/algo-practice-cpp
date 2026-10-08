#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static vector<int> order(int n) {
    vector<int> out;
    for (int lo = 0, hi = n - 1; lo <= hi; ++lo, --hi) {
        out.push_back(lo);
        if (lo != hi) {
            out.push_back(hi);
        }
    }
    return out;
}

static void run(vector<int> vals) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    Solution().reorderList(head);
    vector<int> want;
    vector<ListNode*> want_nodes;
    for (int i : order(vals.size())) {
        want.push_back(vals[i]);
        want_nodes.push_back(nodes[i]);
    }
    check(list_to_vec(head), want, "head", vals);
    ensure(list_nodes(head) == want_nodes,
           "the values are in the right order, but the nodes must be re-linked, not have their val swapped",
           "head", vals);
}

TEST(examples) {
    run({10, 20, 30, 40});
    run({5, 9, 2, 7, 4});
    run({8});
}

TEST(edge_cases) {
    run({1, 2, 3});
    run({1, 2});
    run({3, 3, 3, 3, 3, 3});
    run({1000, 1, 1000, 1, 1000, 1, 1000});
    run({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
}

TEST(random) {
    Rng rng(143);
    for (int i = 0; i < 300; ++i) {
        run(rng.ints(rng(1, 25), 1, 4));
    }
}

TEST(large) {
    Rng rng(1430);
    run(rng.ints(50000, 1, 1000));
    run(vector<int>(49999, 1));
}

}
