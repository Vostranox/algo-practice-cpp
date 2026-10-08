#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals, int left, int right) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    ListNode* got = Solution().reverseBetween(head, left, right);
    vector<int> want = vals;
    vector<ListNode*> want_nodes = nodes;
    reverse(want.begin() + left - 1, want.begin() + right);
    reverse(want_nodes.begin() + left - 1, want_nodes.begin() + right);
    check(list_to_vec(got), want, "head", vals, "left", left, "right", right);
    ensure(list_nodes(got) == want_nodes,
           "the values are in the right order, but the nodes must be re-linked, not have their val swapped",
           "head", vals, "left", left, "right", right);
}

TEST(examples) {
    run({10, 20, 30, 40, 50, 60}, 2, 5);
    run({7, 3, 9}, 1, 3);
    run({4, 8}, 2, 2);
}

TEST(edge_cases) {
    run({5}, 1, 1);
    run({1, 2}, 1, 2);
    run({1, 2}, 1, 1);
    run({1, 2, 3, 4, 5}, 1, 3);
    run({1, 2, 3, 4, 5}, 3, 5);
    run({1, 2, 3, 4, 5}, 4, 5);
    run({1, 2, 3, 4, 5}, 2, 3);
    run({1, 2, 3, 4, 5}, 3, 3);
    run({-500, 500, 0, -1}, 1, 4);
    run({6, 6, 6, 6, 6}, 2, 4);
}

TEST(every_range) {
    Rng rng(92);
    for (int n = 1; n <= 12; ++n) {
        vector<int> vals = rng.ints(n, -3, 3);
        for (int left = 1; left <= n; ++left) {
            for (int right = left; right <= n; ++right) {
                run(vals, left, right);
            }
        }
    }
}

TEST(random) {
    Rng rng(920);
    for (int i = 0; i < 300; ++i) {
        int n = rng(1, 40);
        int left = rng(1, n), right = rng(left, n);
        run(rng.ints(n, -500, 500), left, right);
    }
}

TEST(large) {
    Rng rng(9200);
    vector<int> vals = rng.ints(500, -500, 500);
    for (auto [l, r] : vector<pair<int, int>>{{1, 500}, {1, 1}, {500, 500}, {1, 499}, {2, 500}, {250, 251}, {137, 402}}) {
        run(vals, l, r);
    }
    run(vector<int>(500, -7), 3, 498);
}

}
