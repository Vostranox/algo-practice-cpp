#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals, int x) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    ListNode* got = Solution().partition(head, x);
    vector<int> want;
    vector<ListNode*> want_nodes;
    for (int pass = 0; pass < 2; ++pass) {
        for (size_t i = 0; i < vals.size(); ++i) {
            if ((vals[i] < x) == (pass == 0)) {
                want.push_back(vals[i]);
                want_nodes.push_back(nodes[i]);
            }
        }
    }
    check(list_to_vec(got), want, "head", vals, "x", x);
    ensure(list_nodes(got) == want_nodes,
           "the values are right, but equal values must keep their original relative order and the nodes "
           "must be re-linked, not have their val changed",
           "head", vals, "x", x);
}

TEST(examples) {
    run({5, 1, 8, 3, 6, 2}, 4);
    run({3, 1}, 2);
    run({4, 7, 4}, 4);
}

TEST(edge_cases) {
    run({}, 0);
    run({5}, 5);
    run({5}, 6);
    run({1, 2, 3}, 0);
    run({1, 2, 3}, 10);
    run({3, 2, 1}, 2);
    run({2, 2, 1, 1, 2, 1}, 2);
    run({-100, 100, -100, 100}, -200);
    run({-100, 100, -100, 100}, 200);
    run({100, -100, 100, -100}, 0);
    run({1, 4, 3, 2, 5, 2}, 3);
}

TEST(random) {
    Rng rng(86);
    for (int i = 0; i < 500; ++i) {
        int n = rng(0, 25);
        run(rng.ints(n, -4, 4), rng(-6, 6));
    }
}

TEST(large) {
    Rng rng(860);
    vector<int> vals = rng.ints(200, -100, 100);
    for (int x : {-200, -100, -99, -1, 0, 1, 50, 100, 101, 200}) {
        run(vals, x);
    }
    run(vector<int>(200, 3), 3);
    run(vector<int>(200, 3), 4);
}

}
