#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    ListNode* got = Solution().reverseList(head);
    check(list_to_vec(got), vector<int>(vals.rbegin(), vals.rend()), "head", vals);
    ensure(list_nodes(got) == vector<ListNode*>(nodes.rbegin(), nodes.rend()),
           "the values are right, but the result must be the original nodes re-linked "
           "(don't allocate new nodes or overwrite val)",
           "head", vals);
}

TEST(examples) {
    run({3, 8, -1, 6});
    run({7, 2});
    run({});
}

TEST(edge_cases) {
    run({5});
    run({4, 4});
    run({1, 2, 3});
    run({-5000, 5000, 0});
    run({9, 9, 9, 1, 9});
}

TEST(random) {
    Rng rng(35);
    for (int i = 0; i < 300; ++i) {
        run(rng.ints(rng(0, 20), -5, 5));
    }
}

TEST(large) {
    Rng rng(206);
    run(rng.ints(5000, -5000, 5000));
    run(vector<int>(5000, 7));
}

}
