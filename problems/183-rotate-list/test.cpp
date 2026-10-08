#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals, int k) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    ListNode* got = Solution().rotateRight(head, k);
    vector<int> want = vals;
    vector<ListNode*> want_nodes = nodes;
    if (!vals.empty()) {
        int r = k % static_cast<int>(vals.size());
        rotate(want.begin(), want.end() - r, want.end());
        rotate(want_nodes.begin(), want_nodes.end() - r, want_nodes.end());
    }
    check(list_to_vec(got), want, "head", vals, "k", k);
    ensure(list_nodes(got) == want_nodes,
           "the values are in the right order, but the nodes must be re-linked, not have their val changed",
           "head", vals, "k", k);
}

TEST(examples) {
    run({10, 20, 30, 40, 50}, 2);
    run({8, -1, 6}, 7);
    run({}, 5);
}

TEST(edge_cases) {
    run({}, 0);
    run({}, 2000000000);
    run({9}, 0);
    run({9}, 1);
    run({9}, 13);
    run({1, 2}, 1);
    run({1, 2}, 2);
    run({1, 2, 3, 4, 5}, 0);
    run({1, 2, 3, 4, 5}, 4);
    run({1, 2, 3, 4, 5}, 5);
    run({1, 2, 3, 4, 5}, 6);
    run({-100, 100, 0}, 2000000000);
    run({7, 7, 7, 7}, 3);
}

TEST(small_exhaustive) {
    Rng rng(61);
    for (int n = 1; n <= 12; ++n) {
        vector<int> vals = rng.ints(n, -2, 2);
        for (int k = 0; k <= 3 * n; ++k) {
            run(vals, k);
        }
    }
}

TEST(large) {
    Rng rng(610);
    vector<int> vals = rng.ints(500, -100, 100);
    for (int k : {2000000000, 1999999999, 1999999501, 499, 500, 501, 123456789}) {
        run(vals, k);
    }
    for (int i = 0; i < 20; ++i) {
        int n = rng(1, 500);
        run(rng.ints(n, -100, 100), rng(0, 2000000000));
    }
}

}
