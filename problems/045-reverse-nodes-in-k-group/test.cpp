#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals, int k) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    ListNode* got = Solution().reverseKGroup(head, k);
    vector<int> want = vals;
    vector<ListNode*> want_nodes = nodes;
    for (size_t i = 0; i + k <= vals.size(); i += k) {
        reverse(want.begin() + i, want.begin() + i + k);
        reverse(want_nodes.begin() + i, want_nodes.begin() + i + k);
    }
    check(list_to_vec(got), want, "head", vals, "k", k);
    ensure(list_nodes(got) == want_nodes,
           "the values are in the right order, but the nodes must be re-linked, not have their val swapped",
           "head", vals, "k", k);
}

TEST(examples) {
    run({4, 8, 15, 16, 23, 42, 7, 11}, 3);
    run({3, 1, 2, 5}, 2);
    run({9, 6, 3}, 1);
}

TEST(edge_cases) {
    run({1, 2, 3, 4, 5}, 5);
    run({1, 2, 3, 4, 5}, 4);
    run({1, 2, 3, 4, 5}, 3);
    run({1, 2, 3, 4, 5, 6}, 3);
    run({0}, 1);
    run({5, 5, 5, 5, 5}, 2);
    run({1000, 0, 1000, 0}, 4);
}

TEST(random) {
    Rng rng(25);
    for (int t = 0; t < 500; ++t) {
        int n = rng(1, 20);
        run(rng.ints(n, 0, 3), rng(1, n));
    }
}

TEST(large) {
    Rng rng(250);
    vector<int> vals = rng.ints(5000, 0, 1000);
    for (int k : {1, 2, 7, 2500, 4999, 5000}) {
        run(vals, k);
    }
}

}
