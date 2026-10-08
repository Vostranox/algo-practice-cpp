#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> a, vector<int> b) {
    ListNode* l1 = build_list(a);
    ListNode* l2 = build_list(b);
    vector<ListNode*> nodes = list_nodes(l1), nodes2 = list_nodes(l2);
    nodes.insert(nodes.end(), nodes2.begin(), nodes2.end());
    auto vals_of = [&] {
        vector<int> v;
        for (auto* n : nodes) {
            v.push_back(n->val);
        }
        return v;
    };
    vector<int> vals = vals_of();
    ListNode* got = Solution().mergeTwoLists(l1, l2);
    vector<int> want = a;
    want.insert(want.end(), b.begin(), b.end());
    check(list_to_vec(got), sorted(want), "list1", a, "list2", b);
    vector<ListNode*> got_nodes = list_nodes(got);
    ensure(vals_of() == vals && set<ListNode*>(got_nodes.begin(), got_nodes.end()) == set<ListNode*>(nodes.begin(), nodes.end()),
           "the values are right, but the result must be made of the original nodes spliced together "
           "(no new nodes, no overwritten val)",
           "list1", a, "list2", b);
}

TEST(examples) {
    run({2, 5, 9}, {1, 5, 6, 10});
    run({}, {4});
    run({}, {});
}

TEST(edge_cases) {
    run({3}, {});
    run({1, 2, 3}, {4, 5, 6});
    run({7, 8}, {-100, 0, 1});
    run({2, 2, 2}, {2, 2});
    run({-100, 100}, {-100, 100});
    run({1, 3, 5, 7}, {2, 4, 6, 8});
}

TEST(random) {
    Rng rng(21);
    for (int i = 0; i < 500; ++i) {
        vector<int> a = sorted(rng.ints(rng(0, 50), -10, 10));
        vector<int> b = sorted(rng.ints(rng(0, 50), -10, 10));
        run(a, b);
    }
}

}
