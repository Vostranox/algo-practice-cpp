#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals, int n) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    ListNode* got = Solution().removeNthFromEnd(head, n);
    size_t gone = vals.size() - n;
    vector<int> want = vals;
    want.erase(want.begin() + gone);
    check(list_to_vec(got), want, "head", vals, "n", n);
    vector<ListNode*> want_nodes = nodes;
    want_nodes.erase(want_nodes.begin() + gone);
    bool vals_kept = true;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (i != gone && nodes[i]->val != vals[i]) {
            vals_kept = false;
        }
    }
    ensure(vals_kept && list_nodes(got) == want_nodes,
           "the values are right, but the result must be the original nodes with only node #" + to_string(gone) +
               " (0-based) unlinked (no new nodes, no overwritten val)",
           "head", vals, "n", n);
}

TEST(examples) {
    run({4, 7, 1, 9, 3}, 2);
    run({5, 8}, 2);
    run({6}, 1);
}

TEST(edge_cases) {
    run({1, 2}, 1);
    run({0, 1, 2, 3}, 4);
    run({2, 2, 2, 2}, 3);
    run({100, 0}, 1);
    run({6}, 1);
}

TEST(every_position) {
    Rng rng(19);
    for (int size = 1; size <= 30; ++size) {
        vector<int> vals = rng.ints(size, 0, 3);
        for (int n = 1; n <= size; ++n) {
            run(vals, n);
        }
    }
}

}
